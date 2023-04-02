// CWindowsPage.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CWindowsPage.h"


// CWindowsPage dialog

IMPLEMENT_DYNAMIC(CWindowsPage, CMFCPropertyPage)

CWindowsPage::CWindowsPage(HWND hWndCurSel, CWnd* pParent /*=nullptr*/)
	: m_hWndCurSel{ hWndCurSel }
	,CMFCPropertyPage(IDD_DIALOG_WNDPAGE)
	, m_strNextWndHandle(_T(""))
	, m_strNextWndCaption(_T(""))
	, m_strPreviousWndHandle(_T(""))
	, m_strPreviousWndCaption(_T(""))
	, m_strParentWndHandle(_T(""))
	, m_strParentWndCaption(_T(""))
	, m_strFirstChildWndHandle(_T(""))
	, m_strFirstChildWndCaption(_T(""))
	, m_strOwnerWndHandle(_T(""))
	, m_strOwnerWndCaption(_T(""))
{

}

CWindowsPage::~CWindowsPage()
{
}

void CWindowsPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WND_NEXT_HANDLE, m_strNextWndHandle);
	DDX_Text(pDX, IDC_EDIT_WND_NEXT_CAPTION, m_strNextWndCaption);
	DDX_Text(pDX, IDC_EDIT_WND_PREVIOUS_HANDLE, m_strPreviousWndHandle);
	DDX_Text(pDX, IDC_EDIT_WND_PREVIOUS_CAPTION, m_strPreviousWndCaption);
	DDX_Text(pDX, IDC_EDIT_WND_PARENT_HANDLE, m_strParentWndHandle);
	DDX_Text(pDX, IDC_EDIT_WND_PARENT_CAPTION, m_strParentWndCaption);
	DDX_Text(pDX, IDC_EDIT_WND_FIRSTCHILD_HANDLE, m_strFirstChildWndHandle);
	DDX_Text(pDX, IDC_EDIT_WND_FIRSTCHILD_CAPTION, m_strFirstChildWndCaption);
	DDX_Text(pDX, IDC_EDIT_WND_OWNER_HANDLE, m_strOwnerWndHandle);
	DDX_Text(pDX, IDC_EDIT_WND_OWNER_CAPTION, m_strOwnerWndCaption);
}


BEGIN_MESSAGE_MAP(CWindowsPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CWindowsPage message handlers


BOOL CWindowsPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	auto hWndNext = ::GetWindow(m_hWndCurSel, GW_HWNDNEXT);
	m_strNextWndHandle.Format(_T("%p"), hWndNext);
	::GetWindowText(hWndNext, m_strNextWndCaption.GetBufferSetLength(MAXWORD), MAXWORD);

	auto hWndPrev = ::GetWindow(m_hWndCurSel, GW_HWNDPREV);
	m_strPreviousWndHandle.Format(_T("%p"), hWndPrev);
	::GetWindowText(hWndPrev, m_strPreviousWndCaption.GetBufferSetLength(MAXWORD), MAXWORD);

	auto hWndParent = ::GetParent(m_hWndCurSel);
	m_strParentWndHandle.Format(_T("%p"), hWndParent);
	::GetWindowText(hWndParent, m_strParentWndCaption.GetBufferSetLength(MAXWORD), MAXWORD);

	auto hWndFirstChild = ::GetWindow(m_hWndCurSel, GW_CHILD);
	m_strFirstChildWndHandle.Format(_T("%p"), hWndFirstChild);
	::GetWindowText(hWndFirstChild, m_strFirstChildWndCaption.GetBufferSetLength(MAXWORD), MAXWORD);

	auto hWndOwner = ::GetWindow(m_hWndCurSel, GW_OWNER);
	m_strOwnerWndHandle.Format(_T("%p"), hWndOwner);
	::GetWindowText(hWndOwner, m_strOwnerWndCaption.GetBufferSetLength(MAXWORD), MAXWORD);


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
