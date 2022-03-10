
// Lenna_BMPshow.h : main header file for the Lenna_BMPshow application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLennaBMPshowApp:
// See Lenna_BMPshow.cpp for the implementation of this class
//

class CLennaBMPshowApp : public CWinApp
{
public:
	CLennaBMPshowApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLennaBMPshowApp theApp;
