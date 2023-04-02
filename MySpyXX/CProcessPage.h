#pragma once
#include "afxdialogex.h"


// CProcessPage dialog

class CProcessPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CProcessPage)

public:
	CProcessPage(HWND hWndCurSel = NULL, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProcessPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROCESSPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HWND	m_hWndCurSel;
	CString m_strMyProcessID;
	CString m_strMyThreadID;
	virtual BOOL OnInitDialog();
};
