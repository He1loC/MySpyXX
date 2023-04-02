#pragma once
#include "afxdialogex.h"


// CHookMsgDlg dialog

class CHookMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHookMsgDlg)

public:
	CHookMsgDlg(HWND hWnd,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHookMsgDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HOOKMSG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonHookinstall();
	afx_msg void OnBnClickedButtonUnhook();
	HWND m_hCurSelWnd=nullptr;
	HMODULE m_hModForUse = nullptr;
};
