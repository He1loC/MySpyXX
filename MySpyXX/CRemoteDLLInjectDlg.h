#pragma once
#include "afxdialogex.h"


// CRemoteDLLInjectDlg dialog

class CRemoteDLLInjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRemoteDLLInjectDlg)

public:
	CRemoteDLLInjectDlg(HWND hwnd,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRemoteDLLInjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REMOTEDLLINJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_ebcDllLocation;
	HWND m_hCurSelWnd;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
