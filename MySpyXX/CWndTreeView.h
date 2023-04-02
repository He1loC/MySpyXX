#pragma once


// CWndTreeView view
#include <afxcview.h>
#include <map>
#include "MySpyXXDoc.h"

class CWndTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CWndTreeView)

protected:
	CWndTreeView();           // protected constructor used by dynamic creation
	virtual ~CWndTreeView();

public:
	CMySpyXXDoc* GetDocument() const;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	// 初始化窗口树控件
	void InitWndTree();
	virtual void OnInitialUpdate();
	void InsertAllSubWindowTraverse(HWND hWnd, HTREEITEM hItem);
	CString GetWndInfoString(HWND hWnd);
	afx_msg void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightmenuRefresh();
	afx_msg void OnRightmenuProperties();

public:
	std::map<HTREEITEM, HWND> m_TreeItemHWNDTable;
	std::map<HWND, HTREEITEM> m_HWNDTreeItemTable;
	afx_msg void OnRightmenuRemotedllinject();
	afx_msg void OnRightmenuHooksWmCommand();
//	afx_msg void OnUpdateRightmenuHooksWmCommand(CCmdUI* pCmdUI);

	bool m_bIsHookingWMCOMMAND = false;
	afx_msg void OnRightmenuMfcspy();
};

#ifndef _DEBUG  // debug version in CWndTreeView.cpp
inline CMySpyXXDoc* CWndTreeView::GetDocument() const
{
	return reinterpret_cast<CMySpyXXDoc*>(m_pDocument);
}
#endif


