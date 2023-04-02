#pragma once
#include "afxdialogex.h"


// CMyMFCSpyDlg dialog

class CMyMFCSpyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyMFCSpyDlg)

public:
	CMyMFCSpyDlg(HWND hWnd,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMyMFCSpyDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMyMFCSpyDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	HWND m_hCurSelWnd;
	HMODULE m_hDll=NULL;
	HHOOK m_hHook=NULL;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnApp(WPARAM wParam, LPARAM lParam);
public:
	CEdit m_edtInfo;
};
