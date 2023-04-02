#pragma once
#include "afxdialogex.h"


// CClassPage dialog

class CClassPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CClassPage)

public:
	CClassPage(HWND hWndCurSel = NULL, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CClassPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLASSPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HWND	m_hWndCurSel;
	virtual BOOL OnInitDialog();
	CString m_strMyClassName;
	CString m_strMyClassStyles;
	CString m_strMyClassBytes;
	CString m_strMyInstanceHandle;
	CString m_strMyWndProc;
	CString m_strMyMenuName;
	CString m_strMyIconHandle;
	CString m_strMyCursorHandle;
	CString m_strMyBKgndBrush;
	CComboBox m_combClassStyles;
};
