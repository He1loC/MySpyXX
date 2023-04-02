#pragma once
#include "afxdialogex.h"
#include "CMyPicStatic.h"


// CFindWindowDlg dialog

class CFindWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindWindowDlg)

public:
	CFindWindowDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFindWindowDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FINDWINDOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMyPicStatic m_picStatic;
	CString m_strHandle;
	CString m_strCaption;
	CString m_strStyle;
	CString m_strClass;
	CString m_strRect;
	afx_msg void OnEnChangeEditFindwndHandle();
	afx_msg void OnBnClickedOk();
};
