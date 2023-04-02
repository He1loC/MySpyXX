// CHookMsgDlg.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CHookMsgDlg.h"


// CHookMsgDlg dialog

IMPLEMENT_DYNAMIC(CHookMsgDlg, CDialogEx)

CHookMsgDlg::CHookMsgDlg(HWND hWnd, CWnd* pParent /*=nullptr*/)
	:m_hCurSelWnd{ hWnd }
	,CDialogEx(IDD_DIALOG_HOOKMSG, pParent)
{
    m_hModForUse = ::LoadLibrary(_T("MyHookDll"));
    if (!m_hModForUse)
    {
        AfxMessageBox(_T("º”‘ÿ ß∞‹£°"));
    }
}

CHookMsgDlg::~CHookMsgDlg()
{
    if (!m_hModForUse)
    {
        ::FreeLibrary(m_hModForUse);
    }
}

void CHookMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHookMsgDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HOOKINSTALL, &CHookMsgDlg::OnBnClickedButtonHookinstall)
	ON_BN_CLICKED(IDC_BUTTON_UNHOOK, &CHookMsgDlg::OnBnClickedButtonUnhook)
END_MESSAGE_MAP()


// CHookMsgDlg message handlers
using pfnInstallHook = void (*)(DWORD tid);
using pfnUninstallHook = void (*)(void);

void CHookMsgDlg::OnBnClickedButtonHookinstall()
{



        auto p = (pfnInstallHook)::GetProcAddress(m_hModForUse, "InstallHook");
        auto tid = ::GetWindowThreadProcessId(m_hCurSelWnd, nullptr);
        p(tid);

        ::PostThreadMessage(tid, WM_NULL, 0, 0);

}


void CHookMsgDlg::OnBnClickedButtonUnhook()
{
    auto p = (pfnUninstallHook)::GetProcAddress(m_hModForUse, "UninstallHook");
    p();
}
