// CClassPage.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CClassPage.h"


// CClassPage dialog

IMPLEMENT_DYNAMIC(CClassPage, CMFCPropertyPage)

CClassPage::CClassPage(HWND hWndCurSel, CWnd* pParent /*=nullptr*/)
	: m_hWndCurSel{ hWndCurSel }
	, CMFCPropertyPage(IDD_DIALOG_CLASSPAGE)
	, m_strMyClassName(_T(""))
	, m_strMyClassStyles(_T(""))
	, m_strMyClassBytes(_T(""))
	, m_strMyInstanceHandle(_T(""))
	, m_strMyWndProc(_T(""))
	, m_strMyMenuName(_T(""))
	, m_strMyIconHandle(_T(""))
	, m_strMyCursorHandle(_T(""))
	, m_strMyBKgndBrush(_T(""))
{

}

CClassPage::~CClassPage()
{
}

void CClassPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CLASS_CLASSNAME, m_strMyClassName);
	DDX_Text(pDX, IDC_EDIT_CLASS_CLASSSYTLES, m_strMyClassStyles);
	DDX_Text(pDX, IDC_EDIT_CLASS_CLASSBYTES, m_strMyClassBytes);
	DDX_Text(pDX, IDC_EDIT_CLASS_INSTANCE_HANDLE, m_strMyInstanceHandle);
	DDX_Text(pDX, IDC_EDIT_CLASS_WNDPROC, m_strMyWndProc);
	DDX_Text(pDX, IDC_EDIT_CLASS_MENU_NAME, m_strMyMenuName);
	DDX_Text(pDX, IDC_EDIT_CLASS_ICON_HANDLE, m_strMyIconHandle);
	DDX_Text(pDX, IDC_EDIT_CLASS_CURSOR_HANDLE, m_strMyCursorHandle);
	DDX_Text(pDX, IDC_EDIT_CLASS_BKGND_BRUSH, m_strMyBKgndBrush);
	DDX_Control(pDX, IDC_COMBO_CLASSSTYLES, m_combClassStyles);
}


BEGIN_MESSAGE_MAP(CClassPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CClassPage message handlers


BOOL CClassPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	::GetClassName(m_hWndCurSel, m_strMyClassName.GetBufferSetLength(MAXWORD), MAXWORD);

	auto styles=::GetClassLongPtr(m_hWndCurSel, GCL_STYLE);
	m_strMyClassStyles.Format(_T("%08X"), styles);

	if (styles & CS_VREDRAW)
	{
		m_combClassStyles.AddString(_T("CS_VREDRAW"));
	}
	if (styles & CS_HREDRAW)
	{
		m_combClassStyles.AddString(_T("CS_HREDRAW"));
	}
	if (styles & CS_DBLCLKS)
	{
		m_combClassStyles.AddString(_T("CS_DBLCLKS"));
	}
	if (styles & CS_OWNDC)
	{
		m_combClassStyles.AddString(_T("CS_OWNDC"));
	}
	if (styles & CS_CLASSDC)
	{
		m_combClassStyles.AddString(_T("CS_CLASSDC"));
	}
	if (styles & CS_PARENTDC)
	{
		m_combClassStyles.AddString(_T("CS_PARENTDC"));
	}
	if (styles & CS_NOCLOSE)
	{
		m_combClassStyles.AddString(_T("CS_NOCLOSE"));
	}
	if (styles & CS_SAVEBITS)
	{
		m_combClassStyles.AddString(_T("CS_SAVEBITS"));
	}
	if (styles & CS_BYTEALIGNCLIENT)
	{
		m_combClassStyles.AddString(_T("CS_BYTEALIGNCLIENT"));
	}
	if (styles & CS_BYTEALIGNWINDOW)
	{
		m_combClassStyles.AddString(_T("CS_BYTEALIGNWINDOW"));
	}
	if (styles & CS_GLOBALCLASS)
	{
		m_combClassStyles.AddString(_T("CS_GLOBALCLASS"));
	}


	if (styles & CS_IME)
	{
		m_combClassStyles.AddString(_T("CS_IME"));
	}

	if (styles & CS_DROPSHADOW)
	{
		m_combClassStyles.AddString(_T("CS_DROPSHADOW"));
	}

	m_combClassStyles.SetCurSel(0);

	auto classbytes = ::GetClassLongPtr(m_hWndCurSel, GCL_CBCLSEXTRA);
	m_strMyClassBytes.Format(_T("%d"), classbytes);

	auto hInstance=(HINSTANCE)::GetWindowLongPtr(m_hWndCurSel, GWLP_HINSTANCE);
	m_strMyInstanceHandle.Format(_T("%p"), hInstance);

	
	auto windproc = ::GetClassLongPtr(m_hWndCurSel, GCLP_WNDPROC);
	m_strMyWndProc.Format(_T("%p"), windproc);

	auto menuname = (LPCSTR)::GetClassLongPtr(m_hWndCurSel, GCLP_MENUNAME);
	m_strMyMenuName = menuname;

	auto hIcon = (LPCSTR)::GetClassLongPtr(m_hWndCurSel, GCLP_HICON);
	m_strMyIconHandle.Format(_T("%p"), hIcon);

	auto hCursor = (LPCSTR)::GetClassLongPtr(m_hWndCurSel, GCLP_HCURSOR);
	m_strMyCursorHandle.Format(_T("%p"), hCursor);

	auto hBrush = (LPCSTR)::GetClassLongPtr(m_hWndCurSel, GCLP_HBRBACKGROUND);
	m_strMyBKgndBrush.Format(_T("%p"), hBrush);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
