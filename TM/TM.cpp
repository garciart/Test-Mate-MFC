// TM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TM.h"
#include "TMDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTMApp

BEGIN_MESSAGE_MAP(CTMApp, CWinApp)

END_MESSAGE_MAP()


// CTMApp construction

CTMApp::CTMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTMApp object

CTMApp theApp;


// CTMApp initialization

BOOL CTMApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

#if _MSC_VER==1400 && defined(_UNICODE) && !defined(_AFXDLL)
	AFX_MODULE_STATE* pStatus=AfxGetModuleState();
	delete pStatus->m_pDllIsolationWrappers[_AFX_COMMDLG_ISOLATION_WRAPPER_INDEX];
	pStatus->m_pDllIsolationWrappers[_AFX_COMMDLG_ISOLATION_WRAPPER_INDEX]=new CCommDlgWrapper; //to use unicows.dll
#endif

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// Create mutex

	COleDateTime m_dateCheck;
	m_dateCheck = COleDateTime::GetCurrentTime();
	if((m_dateCheck.GetYear() == 2009) && (m_dateCheck.GetDayOfYear() >= 91))
	{
		remove("\\TM\\tm.pfl");
		MessageBox(NULL, L"Your evaluation period has expired.  Please contact us at test_mate@shorens.com as soon as possible.", L"Test Mate", MB_ICONSTOP);
		exit(0);
	}

	hMutex = ::CreateMutex(NULL, TRUE, L"GlobalMutex");
	
	switch(::GetLastError())
	{
	case ERROR_SUCCESS:
		// Mutex created successfully. There is no instance running
		break;
	case ERROR_ALREADY_EXISTS:
		// Mutex already exists so there is a running instance of our app.
		MessageBox(NULL, L"Test Mate is already running!", L"Test Mate", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	default:
		// Failed to create mutex by unknown reason
		MessageBox(NULL, L"Cannot start Test Mate.  Please contact us test_mate@shorens.com as soon as possible.", L"Test Mate", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	CLoginDlg dlgLogin;
	INT_PTR nResponse = dlgLogin.DoModal();

	if(nResponse != IDOK)
	{
		return FALSE;
	}
	else
	{
		m_strLoginKey.Format(L"%s", dlgLogin.m_strPassword);
	}

	CTMDlg dlg;
	dlg.m_strKey.Format(L"%s", m_strLoginKey);
	m_pMainWnd = &dlg;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
