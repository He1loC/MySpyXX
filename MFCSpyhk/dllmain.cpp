// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <psapi.h>


struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;   // windows message
	UINT nCode;      // control code or WM_NOTIFY code
	UINT nID;        // control ID (or 0 for windows messages)
	UINT nLastID;    // used for entries specifying a range of control id's
	UINT_PTR nSig;       // signature type (action) or pointer to message #
	void* pfn;    // routine to call (or special value)
};


struct tagSpyInfo
{
	char g_szAllClassName[512][260] = {};
	int g_nNumOfClasses = 0;

	AFX_MSGMAP_ENTRY g_MsgMap[512] = {};
	int g_nMsgEntry = 0;

	bool g_bIsWndProcInDll = false;
	bool g_bIsDebug = false;

	uintptr_t vTable[512]{};
	int n_numOfVFunc = 0;
};



#pragma data_seg(".shared")
DWORD g_ThreadId = 0;
HHOOK g_hHook = nullptr;
HWND  g_hTargetWnd = 0;

tagSpyInfo g_SpyInfo{};

#pragma data_seg()
#pragma comment(linker, "/section:.shared,RWS")








struct AFX_MSGMAP
{
	AFX_MSGMAP* (__stdcall* pfnGetBaseMap)();
	AFX_MSGMAP_ENTRY* lpEntries;
};


class CObject {

};


struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
	//#ifdef _AFXDLL
	//  CRunti*meClass* (PASCAL* m_pfnGetBaseClass)();
	//#else
	CRuntimeClass* m_pBaseClass;
	//#endif
};



class CWnd
{
public:
	virtual CRuntimeClass* GetRuntimeClass() = 0;
};


class CCmdTarget
{
public:
	virtual AFX_MSGMAP* GetMessageMap() { return NULL; };
};


typedef CWnd* (__stdcall* CWnd_FromHandlePermanent)(HWND);

void DoWork();

void* SearchFromHandlePermanent(void* pStartAddr);


extern "C" LRESULT WINAPI MFCSpyHookFunc(int nCode, WPARAM wParam, LPARAM lParam)
{


	static bool  bFirstTime = true;

	if (bFirstTime)
	{
		DoWork();
		bFirstTime = !bFirstTime;
	}





	while (g_hHook == nullptr) {}

	// do nothing only for loading dll
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

extern "C" void SetSharedData(DWORD dwCallerThreadId, HHOOK hHook, HWND  hTargetWnd)
{
	g_ThreadId = dwCallerThreadId;
	g_hHook = hHook;
	g_hTargetWnd = hTargetWnd;

}

extern "C" tagSpyInfo * SpyGetInfo()
{
	

	return &g_SpyInfo;

}


void DoWork()
{
	// 1.��ȡ���ڹ��̺���
	UCHAR* WndProc = 0;  //AfxWndProc
	if (IsWindowUnicode(g_hTargetWnd))
		WndProc = (UCHAR*)GetWindowLongPtrW(g_hTargetWnd, GWL_WNDPROC);
	else
		WndProc = (UCHAR*)GetWindowLongPtrA(g_hTargetWnd, GWL_WNDPROC);
	
	
	// 2.��λCWnd::FromHandlePermanent
	auto pfnFromHandlePermanent = (CWnd_FromHandlePermanent)SearchFromHandlePermanent(WndProc);


	// 3.���õ�CWnd *
	auto pCWnd = pfnFromHandlePermanent(g_hTargetWnd);


	// 4.CWnd *��һ��ΪGetRuntimeClass,�õ�ֱ�����������RTTI
	CRuntimeClass* pRuntimeClass = pCWnd->GetRuntimeClass();
	while (pRuntimeClass)
	{
		strcpy_s(g_SpyInfo.g_szAllClassName[g_SpyInfo.g_nNumOfClasses], pRuntimeClass->m_lpszClassName);
		g_SpyInfo.g_nNumOfClasses++;

		if (g_SpyInfo.g_bIsWndProcInDll)
		{
			using PFN_GetBaseClass = CRuntimeClass* (PASCAL*)();
			//CRuntimeClass* (PASCAL* m_pfnGetBaseClass)();
			auto pfnGetBaseClass = (PFN_GetBaseClass)pRuntimeClass->m_pBaseClass;
			pRuntimeClass = pfnGetBaseClass();
		}
		else
		{
			pRuntimeClass = pRuntimeClass->m_pBaseClass;
		}
		

	}


	DWORD* pVFunc = *(DWORD**)pCWnd;
	while (*pVFunc)
	{
		g_SpyInfo.vTable[g_SpyInfo.n_numOfVFunc] = *pVFunc;
		g_SpyInfo.n_numOfVFunc++;
		pVFunc++;
	}


	// 5.��ȡ��Ϣӳ���,�ȵõ�GetMessageMap������е�λ��(��汾������ѡ�����)
	CCmdTarget obj;
	CCmdTarget* pCmdTarget = &obj;
	//�޸����λ�ã���GetMessageMap��Ϊ��һ��
	*(int*)pCmdTarget = *(int*)pCWnd + 12 * sizeof(uintptr_t);
	AFX_MSGMAP* pMsgMap = pCmdTarget->GetMessageMap();
	AFX_MSGMAP_ENTRY* pEntry = pMsgMap->lpEntries;
	while (pEntry != NULL && pEntry->nSig != 0)
	{
		g_SpyInfo.g_MsgMap[g_SpyInfo.g_nMsgEntry] = *pEntry;

		pEntry++;
		g_SpyInfo.g_nMsgEntry++;
	}


	// final�����õ���ȫ����������ṹ�壬֪ͨSpy��ȡ
	auto hWindow = ::FindWindow(nullptr, TEXT("MFCSpy"));
	::PostMessage(hWindow, WM_APP, 0, 0);

	

}


void* SearchFromHandlePermanent(void* pStartAddr)
{
	UCHAR* pCurAddr = (UCHAR*)pStartAddr;
	// �жϴ˹��̺���������ģ�黹����DLL����Ǿ�̬���ӻ��Ƕ�̬����
	auto hMod = ::GetModuleHandle(nullptr);	//���ص�����ģ����

	IMAGE_DOS_HEADER* pDosHdr = (IMAGE_DOS_HEADER*)hMod;
	IMAGE_NT_HEADERS* pNTHdr = (IMAGE_NT_HEADERS*)((UCHAR*)hMod + pDosHdr->e_lfanew);

	auto dwSizeOfImage = pNTHdr->OptionalHeader.SizeOfImage;

	if ((uintptr_t)pCurAddr < (uintptr_t)hMod || (uintptr_t)pCurAddr >(uintptr_t)hMod + dwSizeOfImage)
	{
		g_SpyInfo.g_bIsWndProcInDll = true;
	}



	// �жϲ�ͬ�汾,���������VS2022�µ� MFC140�� ��ͬ��������ѡ��
	if (g_SpyInfo.g_bIsWndProcInDll)   //��̬����
	{
		
	}
	else				//��̬����
	{
		if (*pCurAddr == 0xE9)		//DEBUG�µ�����
		{
			pCurAddr = pCurAddr + *(int*)(pCurAddr + 1) + 5;
			g_SpyInfo.g_bIsDebug = true;
		}
			

		while (*pCurAddr != 0xE8)
			pCurAddr++;

		pCurAddr = *(int*)(pCurAddr + 1) + pCurAddr + 5;


		return pCurAddr;
	}
	
	return nullptr;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{

		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

