// CMyWndPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "CMyWndPropertySheet.h"


// CMyWndPropertySheet

IMPLEMENT_DYNAMIC(CMyWndPropertySheet, CMFCPropertySheet)

CMyWndPropertySheet::CMyWndPropertySheet(HWND hWnd)
    :m_hWndCurSel{hWnd}
    ,m_generalPage{hWnd}
    ,m_stylesPage{hWnd}
    ,m_windowsPage{hWnd}
    ,m_classPage{hWnd}
    ,m_processPage{hWnd}
{
    AddPage(&m_generalPage);
    AddPage(&m_stylesPage);
    AddPage(&m_windowsPage);
    AddPage(&m_classPage);
    AddPage(&m_processPage);
}

CMyWndPropertySheet::~CMyWndPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyWndPropertySheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// CMyWndPropertySheet message handlers


