// CWndTreeView.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "CWndTreeView.h"

#include "CMyWndPropertySheet.h"
#include <memory>
#include "CRemoteDLLInjectDlg.h"

#include "RemoteDLLInject.h"
#include "CHookMsgDlg.h"
#include "CMyMFCSpyDlg.h"

// CWndTreeView

IMPLEMENT_DYNCREATE(CWndTreeView, CTreeView)

CWndTreeView::CWndTreeView()
{

}

CWndTreeView::~CWndTreeView()
{
}

BEGIN_MESSAGE_MAP(CWndTreeView, CTreeView)
    ON_NOTIFY_REFLECT(NM_RCLICK, &CWndTreeView::OnNMRClick)
    ON_COMMAND(ID_RIGHTMENU_REFRESH, &CWndTreeView::OnRightmenuRefresh)
    ON_COMMAND(ID_RIGHTMENU_PROPERTIES, &CWndTreeView::OnRightmenuProperties)
    ON_COMMAND(ID_RIGHTMENU_REMOTEDLLINJECT, &CWndTreeView::OnRightmenuRemotedllinject)
    ON_COMMAND(ID_RIGHTMENU_HOOKS_WM_COMMAND, &CWndTreeView::OnRightmenuHooksWmCommand)
//    ON_UPDATE_COMMAND_UI(ID_RIGHTMENU_HOOKS_WM_COMMAND, &CWndTreeView::OnUpdateRightmenuHooksWmCommand)
ON_COMMAND(ID_RIGHTMENU_MFCSPY, &CWndTreeView::OnRightmenuMfcspy)
END_MESSAGE_MAP()


// CWndTreeView diagnostics

#ifdef _DEBUG
void CWndTreeView::AssertValid() const
{
    CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CWndTreeView::Dump(CDumpContext& dc) const
{
    CTreeView::Dump(dc);
}
#endif

CMySpyXXDoc* CWndTreeView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpyXXDoc)));
    return (CMySpyXXDoc*)m_pDocument;
}

#endif //_DEBUG


// CWndTreeView message handlers


BOOL CWndTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class
    cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
    return CTreeView::PreCreateWindow(cs);
}



// 初始化窗口树控件
void CWndTreeView::InitWndTree()
{
    // TODO: Add your implementation code here.
    auto& tree = GetTreeCtrl();

    //清空所有
    tree.DeleteAllItems();
    m_TreeItemHWNDTable.clear();
    m_HWNDTreeItemTable.clear();

    // 问题，桌面窗口是否是所有窗口的父窗口？
    // 获取窗口句柄
    auto hDesktop = ::GetDesktopWindow();


    // 添加桌面窗口
    auto hRoot = tree.InsertItem(GetWndInfoString(hDesktop));
    //tree.InsertItem(_T(""), hRoot);
    m_TreeItemHWNDTable.insert({ hRoot,hDesktop });
    m_HWNDTreeItemTable.insert({ hDesktop , hRoot });
    InsertAllSubWindowTraverse(hDesktop, hRoot);
}


void CWndTreeView::OnInitialUpdate()
{
    CTreeView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    InitWndTree();
}

void CWndTreeView::InsertAllSubWindowTraverse(HWND hWnd, HTREEITEM hItem)
{
    auto hChildWnd = ::GetWindow(hWnd, GW_CHILD);
    if (hChildWnd == NULL)
    {
        return;
    }

    do
    {
        auto hChildItem = GetTreeCtrl().InsertItem(GetWndInfoString(hChildWnd), hItem);

        m_TreeItemHWNDTable.insert({ hChildItem,hChildWnd });
        m_HWNDTreeItemTable.insert({ hChildWnd , hChildItem });

        InsertAllSubWindowTraverse(hChildWnd, hChildItem);

        hChildWnd = ::GetWindow(hChildWnd, GW_HWNDNEXT);

    } while (hChildWnd != NULL);

}


CString CWndTreeView::GetWndInfoString(HWND hWnd)
{
    //获取窗口标题
    TCHAR strWindowText[MAX_PATH] = { 0 };
    ::GetWindowText(hWnd, strWindowText, MAX_PATH);

    //获取窗口类名
    TCHAR strWindowClassName[MAX_PATH] = { 0 };
    ::GetClassName(hWnd, strWindowClassName, MAX_PATH);

    //将窗口句柄、窗口标题、窗口类名格式化
    CString strFmt;
    strFmt.Format(_T("Window %p \"%s\" %s"), (unsigned int)hWnd, strWindowText, strWindowClassName);
    return strFmt;
}



void CWndTreeView::OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    auto& tree = GetTreeCtrl();
    CMenu menu;
    menu.LoadMenu(IDR_MENU_RIGHT);
    auto pSubMn = menu.GetSubMenu(0);

    CPoint pt;
    ::GetCursorPos(&pt);

    tree.ScreenToClient(&pt);

    UINT uFlags = 0;
    HTREEITEM hItem = tree.HitTest(pt, &uFlags);

    if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
    {
        tree.SelectItem(hItem);
    }
    else
    {
        pSubMn->EnableMenuItem(ID_RIGHTMENU_PROPERTIES, MF_BYCOMMAND | MF_DISABLED);
        tree.SelectItem(NULL);
    }

    // 弹出子菜单
    tree.ClientToScreen(&pt);
    pSubMn->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x,
        pt.y, this);

    *pResult = 0;
}


void CWndTreeView::OnRightmenuRefresh()
{
    InitWndTree();
}


void CWndTreeView::OnRightmenuProperties()
{
    // TODO: Add your command handler code here
    auto& tree = GetTreeCtrl();
    auto hSelItem = tree.GetSelectedItem();
    CMyWndPropertySheet sheet{ m_TreeItemHWNDTable[hSelItem] };
    sheet.DoModal();
    /*auto pSheet = std::make_unique<CMyWndPropertySheet>(m_TreeItemHWNDTable[hSelItem]);

    pSheet->DoModal();*/
}


void CWndTreeView::OnRightmenuRemotedllinject()
{
    auto& tree = GetTreeCtrl();
    auto hSelItem = tree.GetSelectedItem();
    CRemoteDLLInjectDlg dlg{ m_TreeItemHWNDTable[hSelItem] };
    dlg.DoModal();
}





void CWndTreeView::OnRightmenuHooksWmCommand()
{
    auto& tree = GetTreeCtrl();
    auto hSelItem = tree.GetSelectedItem();

    CHookMsgDlg dlg{ m_TreeItemHWNDTable[hSelItem] };
    dlg.DoModal();
    
}


//void CWndTreeView::OnUpdateRightmenuHooksWmCommand(CCmdUI* pCmdUI)
//{
    // TODO: Add your command update UI handler code here
//    pCmdUI->SetCheck(m_bIsHookingWMCOMMAND == true);
//}


void CWndTreeView::OnRightmenuMfcspy()
{


    auto& tree = GetTreeCtrl();
    auto hSelItem = tree.GetSelectedItem();

    // 发送消息检查是否是MFC窗口
    if (!::SendMessage(m_TreeItemHWNDTable[hSelItem], WM_QUERYAFXWNDPROC, NULL, NULL))
    {
        AfxMessageBox(_T("Not A MFC window!"));
        return;
    }


    CMyMFCSpyDlg dlg{ m_TreeItemHWNDTable[hSelItem] };
    dlg.DoModal();
}
