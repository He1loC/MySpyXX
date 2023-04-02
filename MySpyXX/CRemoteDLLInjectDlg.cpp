// CRemoteDLLInjectDlg.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CRemoteDLLInjectDlg.h"
#include "RemoteDLLInject.h"


// CRemoteDLLInjectDlg dialog

IMPLEMENT_DYNAMIC(CRemoteDLLInjectDlg, CDialogEx)

CRemoteDLLInjectDlg::CRemoteDLLInjectDlg(HWND hwnd, CWnd* pParent /*=nullptr*/)
	: m_hCurSelWnd{hwnd}
	,CDialogEx(IDD_DIALOG_REMOTEDLLINJECT, pParent)
{

}

CRemoteDLLInjectDlg::~CRemoteDLLInjectDlg()
{
}

void CRemoteDLLInjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_REMOTEDLLINJECT_DLLLOC, m_ebcDllLocation);
}


BEGIN_MESSAGE_MAP(CRemoteDLLInjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRemoteDLLInjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CRemoteDLLInjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_ebcDllLocation.GetWindowText(str);

	USES_CONVERSION;
	auto szDllPath = T2A(str);
	int i = 0;
	
	if (::RemoteDllInject(m_hCurSelWnd, szDllPath))
	{
		AfxMessageBox(_T("注入成功"));
	}
	else
	{
		AfxMessageBox(_T("注入失败"));
	}


	CDialogEx::OnOK();
}


BOOL CRemoteDLLInjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ebcDllLocation.EnableFileBrowseButton(_T("dll"), _T("dll files|*.dll||")); //filter file but *.dll

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
