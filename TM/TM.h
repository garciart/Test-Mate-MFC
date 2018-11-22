// TM.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTMApp:
// See TM.cpp for the implementation of this class
//

class CTMApp : public CWinApp
{
public:
	CTMApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

private:
	HANDLE hMutex;
public:
	CString m_strLoginKey;
};

extern CTMApp theApp;