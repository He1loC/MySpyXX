#pragma once
#include "afxdialogex.h"


// CGeneralPage dialog

class CGeneralPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CGeneralPage)

public:
	CGeneralPage(HWND hWndCurSel=NULL, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGeneralPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENERALPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HWND	m_hWndCurSel;
	CString m_strCaption;
	CString m_strWndHandle;
	CString m_strWndProc;
	CString m_strWndRect;
	CString m_strRrestoredRect;
	CString m_strClientRect;
	CString m_strInstanceHandle;
	CString m_strMenuHandle;
	CString m_strUserData;
	virtual BOOL OnInitDialog();
};
