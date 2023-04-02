// CGeneralPage.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CGeneralPage.h"


// CGeneralPage dialog

IMPLEMENT_DYNAMIC(CGeneralPage, CMFCPropertyPage)

CGeneralPage::CGeneralPage(HWND hWndCurSel,CWnd* pParent /*=nullptr*/)
	: m_hWndCurSel{hWndCurSel}
	, CMFCPropertyPage(IDD_DIALOG_GENERALPAGE)
	, m_strCaption(_T(""))
	, m_strWndHandle(_T(""))
	, m_strWndProc(_T(""))
	, m_strWndRect(_T(""))
	, m_strRrestoredRect(_T(""))
	, m_strClientRect(_T(""))
	, m_strInstanceHandle(_T(""))
	, m_strMenuHandle(_T(""))
	, m_strUserData(_T(""))
{
	
}

CGeneralPage::~CGeneralPage()
{
}

void CGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WNDCAPTIOIN, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_WNDHANDLE, m_strWndHandle);
	DDX_Text(pDX, IDC_EDIT_WNDPROC, m_strWndProc);
	DDX_Text(pDX, IDC_EDIT_WNDRECT, m_strWndRect);
	DDX_Text(pDX, IDC_EDIT_WNDRESTOREDRECT, m_strRrestoredRect);
	DDX_Text(pDX, IDC_EDIT_WNDCLIENTRECT, m_strClientRect);
	DDX_Text(pDX, IDC_EDIT_WND_INSTANCE_HANDLE, m_strInstanceHandle);
	DDX_Text(pDX, IDC_EDIT_MENU_HANDLE, m_strMenuHandle);
	DDX_Text(pDX, IDC_EDIT_USER_DATA, m_strUserData);
}


BEGIN_MESSAGE_MAP(CGeneralPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CGeneralPage message handlers


BOOL CGeneralPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	if (::IsWindow(m_hWndCurSel))
	{
		::GetWindowText(m_hWndCurSel, m_strCaption.GetBufferSetLength(MAX_PATH), MAX_PATH);

		m_strWndHandle.Format(_T("%p"), m_hWndCurSel);

		auto lWndProc = ::GetWindowLongPtr(m_hWndCurSel, GWLP_WNDPROC);
		m_strWndProc.Format(_T("%p"), lWndProc);

		WINDOWINFO wi;
		wi.cbSize = sizeof(WINDOWINFO);
		::GetWindowInfo(m_hWndCurSel, &wi);
		WINDOWPLACEMENT wp;
		wp.length = sizeof(WINDOWPLACEMENT);
		::GetWindowPlacement(m_hWndCurSel, &wp);

		CString strShowCmd;
		if (wp.showCmd & SW_NORMAL)
		{
			strShowCmd = _T("Normal");
		}
		else if (wp.showCmd & SW_MINIMIZE)
		{
			strShowCmd = _T("Minimized");
		}
		else if (wp.showCmd & SW_MAXIMIZE)
		{
			strShowCmd = _T("Maximized");
		}
		else if (wp.showCmd & SW_HIDE)
		{
			strShowCmd = _T("Hide");
		}


		CRect rc{ wi.rcWindow };
		m_strWndRect.Format(_T("(%d,%d)-(%d,%d) %dx%d %s"), rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height(), strShowCmd);


		rc = wp.rcNormalPosition;
		m_strRrestoredRect.Format(_T("(%d,%d)-(%d,%d) %dx%d"), rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height());

		rc = wi.rcClient;
		m_strClientRect.Format(_T("(%d,%d)-(%d,%d) %dx%d"), rc.left, rc.top, rc.right, rc.bottom, rc.Width(), rc.Height());

		auto hInstance = ::GetWindowLongPtr(m_hWndCurSel, GWLP_HINSTANCE);
		m_strInstanceHandle.Format(_T("%p"), hInstance);

		auto hMenu = ::GetMenu(m_hWndCurSel);
		m_strMenuHandle.Format(_T("%p"), hMenu);

		auto userData = ::GetWindowLongPtr(m_hWndCurSel, GWLP_USERDATA);
		m_strUserData.Format(_T("%p"), userData);

		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
