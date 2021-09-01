
// Pavlovska_zapocet.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPavlovskazapocetApp:
// See Pavlovska_zapocet.cpp for the implementation of this class
//

class CPavlovskazapocetApp : public CWinApp
{
public:
	CPavlovskazapocetApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPavlovskazapocetApp theApp;
