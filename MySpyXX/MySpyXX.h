
// MySpyXX.h : main header file for the MySpyXX application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMySpyXXApp:
// See MySpyXX.cpp for the implementation of this class
//

class CMySpyXXApp : public CWinApp
{
public:
	CMySpyXXApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMySpyXXApp theApp;
