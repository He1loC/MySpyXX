// CSytlesPage.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CSytlesPage.h"


// CSytlesPage dialog

IMPLEMENT_DYNAMIC(CSytlesPage, CMFCPropertyPage)

CSytlesPage::CSytlesPage(HWND hWndCurSel, CWnd* pParent /*=nullptr*/)
	: m_hWndCurSel{hWndCurSel}
	,CMFCPropertyPage(IDD_DIALOG_STYLESPAGE)
	, m_strWndStyles(_T(""))
	, m_strExSytles(_T(""))
{
	
}

CSytlesPage::~CSytlesPage()
{
}

void CSytlesPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STYLES_WNDSTYLES, m_strWndStyles);
	DDX_Text(pDX, IDC_EDIT_STYLES_WNDEXSTYLES, m_strExSytles);
	DDX_Control(pDX, IDC_LIST_WNDSTYLES, m_LBwndStyles);
	DDX_Control(pDX, IDC_LIST_WNDEXSTYLES, m_LBexStyles);
}


BEGIN_MESSAGE_MAP(CSytlesPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CSytlesPage message handlers


BOOL CSytlesPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	if (::IsWindow(m_hWndCurSel))
	{
		auto styles = ::GetWindowLongPtr(m_hWndCurSel, GWL_STYLE);
		m_strWndStyles.Format(_T("%p"), styles);

		if (!(styles & WS_OVERLAPPED))
		{
			m_LBwndStyles.AddString(_T("WS_OVERLAPPED"));
		}
		else if (styles & WS_POPUP)
		{
			m_LBwndStyles.AddString(_T("WS_POPUP"));
		}
		else if (styles & WS_CHILD)
		{
			m_LBwndStyles.AddString(_T("WS_CHILD"));
		}


		if (styles & WS_MINIMIZE)
		{
			m_LBwndStyles.AddString(_T("WS_MINIMIZE"));
		}
		if (styles & WS_VISIBLE)
		{
			m_LBwndStyles.AddString(_T("WS_VISIBLE"));
		}
		if (styles & WS_CLIPSIBLINGS)
		{
			m_LBwndStyles.AddString(_T("WS_CLIPSIBLINGS"));
		}
		if (styles & WS_CLIPCHILDREN)
		{
			m_LBwndStyles.AddString(_T("WS_CLIPCHILDREN"));
		}
		if (styles & WS_MAXIMIZE)
		{
			m_LBwndStyles.AddString(_T("WS_MAXIMIZE"));
		}
		if (styles & WS_CAPTION)
		{
			m_LBwndStyles.AddString(_T("WS_CAPTION"));
		}
		if (styles & WS_BORDER)
		{
			m_LBwndStyles.AddString(_T("WS_BORDER"));
		}
		if (styles & WS_DLGFRAME)
		{
			m_LBwndStyles.AddString(_T("WS_DLGFRAME"));
		}
		if (styles & WS_VSCROLL)
		{
			m_LBwndStyles.AddString(_T("WS_VSCROLL"));
		}
		if (styles & WS_HSCROLL)
		{
			m_LBwndStyles.AddString(_T("WS_HSCROLL"));
		}
		if (styles & WS_SYSMENU)
		{
			m_LBwndStyles.AddString(_T("WS_SYSMENU"));
		}
		if (styles & WS_THICKFRAME)
		{
			m_LBwndStyles.AddString(_T("WS_THICKFRAME"));
		}
		if (styles & WS_GROUP)
		{
			m_LBwndStyles.AddString(_T("WS_GROUP"));
		}
		if (styles & WS_TABSTOP)
		{
			m_LBwndStyles.AddString(_T("WS_TABSTOP"));
		}

		if (styles & WS_MINIMIZEBOX)
		{
			m_LBwndStyles.AddString(_T("WS_MINIMIZEBOX"));
		}
		if (styles & WS_MAXIMIZEBOX)
		{
			m_LBwndStyles.AddString(_T("WS_MAXIMIZEBOX"));
		}

		auto Exstyles = ::GetWindowLongPtr(m_hWndCurSel, GWL_EXSTYLE);
		m_strExSytles.Format(_T("%p"), Exstyles);

		if (Exstyles & WS_EX_DLGMODALFRAME)
		{
			m_LBexStyles.AddString(_T("WS_EX_DLGMODALFRAME"));
		}
		if (Exstyles & WS_EX_NOPARENTNOTIFY)
		{
			m_LBexStyles.AddString(_T("WS_EX_NOPARENTNOTIFY"));
		}
		if (Exstyles & WS_EX_TOPMOST)
		{
			m_LBexStyles.AddString(_T("WS_EX_TOPMOST"));
		}
		if (Exstyles & WS_EX_ACCEPTFILES)
		{
			m_LBexStyles.AddString(_T("WS_EX_ACCEPTFILES"));
		}
		if (Exstyles & WS_EX_TRANSPARENT)
		{
			m_LBexStyles.AddString(_T("WS_EX_TRANSPARENT"));
		}

		if (Exstyles & WS_EX_MDICHILD)
		{
			m_LBexStyles.AddString(_T("WS_EX_MDICHILD"));
		}
		if (Exstyles & WS_EX_TOOLWINDOW)
		{
			m_LBexStyles.AddString(_T("WS_EX_TOOLWINDOW"));
		}
		if (Exstyles & WS_EX_WINDOWEDGE)
		{
			m_LBexStyles.AddString(_T("WS_EX_WINDOWEDGE"));
		}
		if (Exstyles & WS_EX_CLIENTEDGE)
		{
			m_LBexStyles.AddString(_T("WS_EX_CLIENTEDGE"));
		}
		if (Exstyles & WS_EX_CONTEXTHELP)
		{
			m_LBexStyles.AddString(_T("WS_EX_CONTEXTHELP"));
		}

		if (Exstyles & WS_EX_RIGHT)
		{
			m_LBexStyles.AddString(_T("WS_EX_RIGHT"));
		}
		else
		{
			m_LBexStyles.AddString(_T("WS_EX_LEFT"));
		}

		if (Exstyles & WS_EX_RTLREADING)
		{
			m_LBexStyles.AddString(_T("WS_EX_RTLREADING"));
		}
		else
		{
			m_LBexStyles.AddString(_T("WS_EX_LTRREADING"));
		}

		if (Exstyles & WS_EX_LEFTSCROLLBAR)
		{
			m_LBexStyles.AddString(_T("WS_EX_LEFTSCROLLBAR"));
		}
		else
		{
			m_LBexStyles.AddString(_T("WS_EX_RIGHTSCROLLBAR"));
		}

		if (Exstyles & WS_EX_CONTROLPARENT)
		{
			m_LBexStyles.AddString(_T("WS_EX_CONTROLPARENT"));
		}
		if (Exstyles & WS_EX_STATICEDGE)
		{
			m_LBexStyles.AddString(_T("WS_EX_STATICEDGE"));
		}
		if (Exstyles & WS_EX_APPWINDOW)
		{
			m_LBexStyles.AddString(_T("WS_EX_APPWINDOW"));
		}

		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
