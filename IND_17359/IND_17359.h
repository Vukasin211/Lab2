
// IND_17359.h : main header file for the IND_17359 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CIND17359App:
// See IND_17359.cpp for the implementation of this class
//

class CIND17359App : public CWinApp
{
public:
	CIND17359App() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIND17359App theApp;
