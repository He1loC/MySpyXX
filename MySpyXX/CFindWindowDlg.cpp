// CFindWindowDlg.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CFindWindowDlg.h"


// CFindWindowDlg dialog

IMPLEMENT_DYNAMIC(CFindWindowDlg, CDialogEx)

CFindWindowDlg::CFindWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FINDWINDOW, pParent)
	, m_strHandle(_T(""))
	, m_strCaption(_T(""))
	, m_strStyle(_T(""))
	, m_strClass(_T(""))
	, m_strRect(_T(""))
{

}

CFindWindowDlg::~CFindWindowDlg()
{
}

void CFindWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC_FINDER, m_picStatic);
	DDX_Text(pDX, IDC_EDIT_FINDWND_HANDLE, m_strHandle);
	DDX_Text(pDX, IDC_EDIT_FINDWND_Caption, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_FINDWND_STYLE, m_strStyle);
	DDX_Text(pDX, IDC_EDIT_FINDWND_CLASS, m_strClass);
	DDX_Text(pDX, IDC_EDIT_FINDWND_RECT, m_strRect);
}


BEGIN_MESSAGE_MAP(CFindWindowDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_FINDWND_HANDLE, &CFindWindowDlg::OnEnChangeEditFindwndHandle)
	ON_BN_CLICKED(IDOK, &CFindWindowDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFindWindowDlg message handlers


void CFindWindowDlg::OnEnChangeEditFindwndHandle()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

	auto hWnd = (HWND)_tcstoul(m_strHandle, NULL, 16);

	if (!::IsWindow(hWnd))
	{
		return;
	}
	

	::GetWindowText(hWnd, m_strCaption.GetBufferSetLength(MAXWORD), MAXWORD);
	::GetClassName(hWnd, m_strClass.GetBufferSetLength(MAXWORD), MAXWORD);

	WINDOWINFO wi;
	wi.cbSize = sizeof(WINDOWINFO);
	::GetWindowInfo(hWnd,&wi);
	m_strStyle.Format(_T("%p"), wi.dwStyle);
	CRect rc{ wi.rcWindow };
	m_strRect.Format(_T("(%d,%d)-(%d,%d) %dx%d"), rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height());

	UpdateData(FALSE);
}


void CFindWindowDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here



	CDialogEx::OnOK();
}
