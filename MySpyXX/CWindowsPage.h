#pragma once
#include "afxdialogex.h"


// CWindowsPage dialog

class CWindowsPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CWindowsPage)

public:
	CWindowsPage(HWND hWndCurSel = NULL, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CWindowsPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WNDPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	HWND	m_hWndCurSel;
	CString m_strNextWndHandle;
	CString m_strNextWndCaption;
	CString m_strPreviousWndHandle;
	CString m_strPreviousWndCaption;
	CString m_strParentWndHandle;
	CString m_strParentWndCaption;
	CString m_strFirstChildWndHandle;
	CString m_strFirstChildWndCaption;
	CString m_strOwnerWndHandle;
	CString m_strOwnerWndCaption;
	virtual BOOL OnInitDialog();
};
