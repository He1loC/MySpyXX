// CProcessPage.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "afxdialogex.h"
#include "CProcessPage.h"


// CProcessPage dialog

IMPLEMENT_DYNAMIC(CProcessPage, CMFCPropertyPage)

CProcessPage::CProcessPage(HWND hWndCurSel, CWnd* pParent /*=nullptr*/)
	: m_hWndCurSel{ hWndCurSel }
	, CMFCPropertyPage(IDD_DIALOG_PROCESSPAGE)
	, m_strMyProcessID(_T(""))
	, m_strMyThreadID(_T(""))
{

}

CProcessPage::~CProcessPage()
{
}

void CProcessPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROCESS_PROCID, m_strMyProcessID);
	DDX_Text(pDX, IDC_EDIT_PROCESS_THREEDID, m_strMyThreadID);
}


BEGIN_MESSAGE_MAP(CProcessPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CProcessPage message handlers


BOOL CProcessPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	DWORD processId;
	auto threadId=::GetWindowThreadProcessId(m_hWndCurSel, &processId);
	m_strMyProcessID.Format(_T("%08X"), processId);
	m_strMyThreadID.Format(_T("%08X"), threadId);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
