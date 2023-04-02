#pragma once
#include "afxdialogex.h"


// CSytlesPage dialog

class CSytlesPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CSytlesPage)

public:
	CSytlesPage(HWND hWndCurSel = NULL, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSytlesPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STYLESPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	HWND	m_hWndCurSel;
	CString m_strWndStyles;
	CString m_strExSytles;
	CListBox m_LBwndStyles;
	CListBox m_LBexStyles;
	virtual BOOL OnInitDialog();
};
