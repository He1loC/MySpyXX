#pragma once

#include "CGeneralPage.h"
#include "CSytlesPage.h"
#include "CWindowsPage.h"
#include "CClassPage.h"
#include "CProcessPage.h"

// CMyWndPropertySheet

class CMyWndPropertySheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CMyWndPropertySheet)

public:
	CMyWndPropertySheet(HWND hWnd=NULL);
	virtual ~CMyWndPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HWND m_hWndCurSel;
	CGeneralPage m_generalPage;
	CSytlesPage m_stylesPage;
	CWindowsPage m_windowsPage;
	CClassPage m_classPage;
	CProcessPage m_processPage;
};


