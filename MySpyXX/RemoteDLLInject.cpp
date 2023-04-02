#include "pch.h"
#include "RemoteDLLInject.h"

bool RemoteDllInject(HWND hWnd, char szDllPath[])
{
    DWORD dwPid = {};
    ::GetWindowThreadProcessId(hWnd, &dwPid);
    auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

    if (!hProc)
    {
        AfxMessageBox(_T("Failed to open process"));
        return false;
    }

    //2.获取LoadLibrary的地址
    auto pfnLoadLibrary = ::GetProcAddress(GetModuleHandle(_T("kernel32")), "LoadLibraryA");

    int n = strlen(szDllPath)+1;
    //3.将DLL写入目标进程 这里有多字节和宽字节问题
    auto pAddr = ::VirtualAllocEx(hProc, nullptr, n,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!pAddr)
    {
        AfxMessageBox(_T("Failed to allocate buffer in target process"));
        return false;
    }
    if (!::WriteProcessMemory(hProc, pAddr, szDllPath, n, nullptr))
    {
        AfxMessageBox(_T("Failed to write to target process"));
        return false;
    }


    //4.创建远程线程，加载Dll
    DWORD tId{};
    auto hThread = CreateRemoteThread(hProc, nullptr, 0,
        (LPTHREAD_START_ROUTINE)pfnLoadLibrary, pAddr, 0, &tId);
    if (!hThread)
    {
        AfxMessageBox(_T("Failed to create remote thread"));
        return false;
    }

    TCHAR szBuf[1024] = {};
    wsprintf(szBuf, TEXT("[hook]:cur tid %08X"), tId);
    OutputDebugString(szBuf);

    ::WaitForSingleObject(hThread, INFINITE);

    DWORD dwExitCode{};
    ::GetExitCodeThread(hThread, &dwExitCode);

    ::VirtualFreeEx(hProc, pAddr, 0, MEM_RELEASE);

    ::CloseHandle(hThread);
    ::CloseHandle(hProc);

    return true;
}
