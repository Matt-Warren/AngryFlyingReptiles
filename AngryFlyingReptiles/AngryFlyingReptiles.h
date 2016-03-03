
// AngryFlyingReptiles.h : main header file for the AngryFlyingReptiles application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAngryFlyingReptilesApp:
// See AngryFlyingReptiles.cpp for the implementation of this class
//

class CAngryFlyingReptilesApp : public CWinApp
{
public:
	CAngryFlyingReptilesApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAngryFlyingReptilesApp theApp;
