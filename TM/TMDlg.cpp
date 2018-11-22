// TMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afx.h"
#include "TM.h"
#include "TMDlg.h"
#include "TermDisplayDlg.h"
#include "ImageDlg.h"
#include ".\TMdlg.h"

CImageDlg* g_pDlgImageDlg = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define getrandom(min, max) ((rand() % (int)(((max)+1) - (min))) + (min))

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTMDlg dialog

CTMDlg::CTMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTMDlg::IDD, pParent)
	, m_bJustStartedFlag(true)
	, m_strFileName(_T(""))
	, x(0)
	, y(0)
	, z(0)
	, m_strTemp(_T(""))
	, m_nAddValuePerLine(0)
	, m_strTestTitle(_T(""))
	, m_nMixArrayMaxLimit(0)
	, m_nMixArrayUpperLimit(0)
	, m_nMixArrayKeyNumber(0)
	, m_nNumberOfQuestions(0)
	, m_nCount(0)
	, m_nTrueCount(0)
	, m_bEnableRadio(true)
	, m_nNumberCorrect(0)
	, m_bTestCompleteFlag(false)
	, m_nScoreCount(0)
	, m_strStaticQuestionCounter(_T(""))
	, m_nAlwaysOnTopToggle(0)
	, m_nProvideFeedbackToggle(1)
	, m_nRandomizeQuestionOrderToggle(0)
	, m_nShowClockToggle(1)
	, m_strStaticClock(_T(""))
	, m_nRadioButtonSelected(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_CLOCK, m_strStaticClock);
	DDX_Text(pDX, IDC_STATIC_QUESTIONCOUNTER, m_strStaticQuestionCounter);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadioButtonSelected);
}

BEGIN_MESSAGE_MAP(CTMDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_INITMENUPOPUP()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_STARTNEWTEST, &CTMDlg::OnFileStartNewTest)
	ON_COMMAND(ID_MAIN_SAVECURRENTTEST32799, &CTMDlg::OnMainSaveTheCurrentTest)
	ON_COMMAND(ID_MAIN_LOADAPREVIOUSTEST, &CTMDlg::OnMainLoadAPreviousTest)
	ON_COMMAND(ID_OPTIONS_ALWAYSONTOP, &CTMDlg::OnOptionsAlwaysOnTop)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALWAYSONTOP, &CTMDlg::OnUpdateOptionsAlwaysOnTop)
	ON_COMMAND(ID_OPTIONS_PROVIDEFEEDBACK, &CTMDlg::OnOptionsProvideFeedback)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_PROVIDEFEEDBACK, &CTMDlg::OnUpdateOptionsProvideFeedback)
	ON_COMMAND(ID_OPTIONS_RANDOMIZEQUESTIONORDER, &CTMDlg::OnOptionsRandomizeQuestionOrder)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RANDOMIZEQUESTIONORDER, &CTMDlg::OnUpdateOptionsRandomizeQuestionOrder)
	ON_COMMAND(ID_OPTIONS_SHOWCLOCK, &CTMDlg::OnOptionsShowClock)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWCLOCK, &CTMDlg::OnUpdateOptionsShowClock)
	ON_COMMAND(ID_FILE_EXITTESTMATE, &CTMDlg::OnFileExitTestMate)
	ON_COMMAND(ID_HELP_ABOUTTESTMATE, &CTMDlg::OnHelpAboutTestMate)
	ON_COMMAND(ID_HELP, &CTMDlg::OnHelp)
	ON_BN_CLICKED(IDC_REVIEWBUTTON, &CTMDlg::OnBnClickedReviewButton)
	ON_BN_CLICKED(IDC_SHOW_SCORE, &CTMDlg::OnBnClickedShowScore)
	ON_BN_CLICKED(IDC_NEXTBUTTON, &CTMDlg::OnBnClickedNextButton)
	ON_COMMAND(ID_HELP_ALETTERTOALLSERVICEMEMBERS, &CTMDlg::OnHelpALetterToAllServiceMembers)
END_MESSAGE_MAP()

// CTMDlg message handlers

BOOL CTMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(ID_CLK_TIMER, 1000, NULL);
	GetDlgItem(IDC_STATIC_TESTTITLE)->SetWindowText(L"Welcome to Test Mate");

	m_brush = new CBrush(RGB(255, 255, 255));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CTMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkColor(RGB(255, 255, 255));
	return (HBRUSH)(m_brush->GetSafeHandle());
}

void CTMDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL && (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL || (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 || state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount && pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void CTMDlg::OnFileStartNewTest(void)
{
	// Warn if a test is already open
	if(m_bJustStartedFlag == false && m_bTestCompleteFlag == false)
	{
		switch(MessageBox(L"This will restart the current test. Do you wish to continue?", L"Test Mate", MB_YESNO | MB_ICONQUESTION))
		{
		case IDNO:
			return;
		}
	}
	// Call Open File Dialog Box
	CFileDialog FileDlg(TRUE, L"tm", L"*.tm", 0, L"Test Mate Files (*.tm)|*.tm||");
	FileDlg.m_ofn.lpstrInitialDir = L"\\tm";
	if(FileDlg.DoModal() == IDOK)
	{
		// If no test is open or the user does anything except click on "No", attempt to open a database
		m_strFileName = FileDlg.GetPathName();
		if(OpenFile() == true)
		{
			ResetTest();
			EnableScreen();
			return;
		}
		else
		{
			MessageBox(L"Test Mate cannot open the specified file.", L"Test Mate", MB_ICONERROR);
			return;
		}
	}
	else
		return;
}

bool CTMDlg::OpenFile(void)
{
	// Initialize OpenFile-specific variables and release the memory when complete
	CStdioFile m_fileOpenDataBase;
	CString m_strEncryptedText;
	int m_nNumberOfTerms;
	CString m_strTerm[100];
	int m_nTermImageFlag[100];
	CString m_strTermImageName[100];
	CString m_strTermDefinition[100];
	int m_nNumberOfMC;
	CString m_strMCQuestion[25];
	int m_nMCImageFlag[25];
	CString m_strMCImageName[25];
	int m_nNumberOfMCAnswers[25];
	CString m_strMCAnswers[25][10];
	CString m_strMCExplanation[25];
	int m_nNumberOfTF;
	CString m_strTFQuestion[25];
	int m_nTFImageFlag[25];
	CString m_strTFImageName[25];
	CString m_strTFAnswer[25];
	CString m_strTFExplanation[25];
	int m_n5050SplitMixArray[100];
	int m_nTermChoice;
	int m_nQuestionMixArray[150];
	int m_nAnswerMixArray[150][4];
	srand((unsigned)time(NULL));
	// Attempt to read the file
	if(!m_fileOpenDataBase.Open(m_strFileName, CFile::modeRead))
		return(false);
	x = 0;
	y = 0;
	z = 0;
	m_nAddValuePerLine = 0;
	// Usage: m_strDecryptedText = Crypt(m_strTextToDecrypt.GetBuffer(), _tcslen(m_strTextToDecrypt), m_strKey.GetBuffer(), _tcslen(m_strKey));
	// Read and check database verification data
	// Old: m_fileOpenDataBase.ReadString(m_strEncryptedText);
	m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
	m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
	if(_ttoi(m_strTemp) != 1010010 && _ttoi(m_strTemp) != 1001111 && _ttoi(m_strTemp) != 1000010)
	{
		m_fileOpenDataBase.Close();
		return(false);
	}
	// Read the test title
	m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
	m_strTestTitle = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
	// Check if there are terms
	m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
	m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
	m_nNumberOfTerms = _ttoi(m_strTemp);
	if(m_nNumberOfTerms != 0)
	{
		for(x = 0; x <= m_nNumberOfTerms; x++)
		{
			// Read the term
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTerm[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Check if there is an image.  If so, read the image's name
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nTermImageFlag[x] = _ttoi(m_strTemp);
			if(m_nTermImageFlag[x] == 1)
			{
				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strTermImageName[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			}
			// Read the definition
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTermDefinition[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			z++;
		}
	}
	// Check if there are multiple choice questions
	m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
	m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
	m_nNumberOfMC = _ttoi(m_strTemp);
	if(m_nNumberOfMC != 0)
	{
		for(x = 0; x <= m_nNumberOfMC; x++)
		{
			// Read the question
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strMCQuestion[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Check if there is an image.  If so, read the image's name
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nMCImageFlag[x] = _ttoi(m_strTemp);
			if(m_nMCImageFlag[x] == 1)
			{
				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strMCImageName[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			}
			// Read the total number of choices
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nNumberOfMCAnswers[x] = _ttoi(m_strTemp);
			// Read the choices
			for(y= 0; y <= m_nNumberOfMCAnswers[x]; y++)
			{
				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strMCAnswers[x][y] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			}
			// Read the explanation
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strMCExplanation[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			z++;
		}
	}
	// Check if there are True/False questions
	m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
	m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
	m_nNumberOfTF = _ttoi(m_strTemp);
	if(m_nNumberOfTF != 0)
	{
		for(x = 0; x <= m_nNumberOfTF; x++)
		{
			// Read the question
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTFQuestion[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Check if there is an image.  If so, read the image's name
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nTFImageFlag[x] = _ttoi(m_strTemp);
			if(m_nTFImageFlag[x] == 1)
			{
				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strTFImageName[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			}
			// Read the answer
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTFAnswer[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Read the explanation
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTFExplanation[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			z++;
		}
	}
	m_nNumberOfQuestions = z - 1;

	// Close database
	m_fileOpenDataBase.Close();
	x = 0;
	y = 0;
	z = 0;
	// Assign terms to global matrix
	if(m_nRandomizeQuestionOrderToggle == 1)
	{
		RandomMaker(m_nNumberOfQuestions, m_nNumberOfQuestions, -1);
		for(x = 0; x <= m_nNumberOfQuestions; x++)
		{
			m_nQuestionMixArray[x] = m_nMixArray[x];
		}
	}
	else
	{
		for(x = 0; x <= m_nNumberOfQuestions; x++)
		{
			m_nQuestionMixArray[x] = x;
		}
	}
	if(m_nNumberOfTerms != 0)
	{
		// If terms are present, as user how terms will be displayed
		TermDisplayDlg dlgLogin;
		INT_PTR nResponse = dlgLogin.DoModal();
		m_nTermChoice = dlgLogin.m_nChoiceFlag;
		// Generate a random number matrix for 50/50 Split term choice
		RandomMaker(m_nNumberOfTerms, m_nNumberOfTerms, -1);
		for(x = 0; x <= m_nNumberOfTerms; x++)
		{
			m_n5050SplitMixArray[x] = (m_nMixArray[x] % 2);
		}
		// Assign terms to global matrix
		for(x = 0; x <= m_nNumberOfTerms; x++)
		{
			m_nImageFlag[m_nQuestionMixArray[z]] = m_nTermImageFlag[x];
			m_strImageName[m_nQuestionMixArray[z]] = m_strTermImageName[x];
			m_nNumberOfAnswers[m_nQuestionMixArray[z]] = 3;
			RandomMaker(m_nNumberOfAnswers[m_nQuestionMixArray[z]], m_nNumberOfAnswers[m_nQuestionMixArray[x]], -1);
			for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
			{
				m_nAnswerMixArray[m_nQuestionMixArray[z]][y] = m_nMixArray[y];
			}
			m_nMixArrayMaxLimit = m_nNumberOfTerms;
			m_nMixArrayUpperLimit = m_nNumberOfAnswers[m_nQuestionMixArray[z]];
			m_nMixArrayKeyNumber = x;
			RandomMaker(m_nMixArrayMaxLimit, m_nMixArrayUpperLimit, m_nMixArrayKeyNumber);
			// Assign term answers as request by user
			switch(m_nTermChoice)
			{
			case 1:
				m_strQuestion[m_nQuestionMixArray[z]] = m_strTermDefinition[x];
				for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
				{
					m_strAnswers[m_nQuestionMixArray[z]][m_nAnswerMixArray[m_nQuestionMixArray[z]][y]] = m_strTerm[m_nMixArray[y]];
					m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strTerm[z];
				}
				break;
			case 2:
				m_strQuestion[m_nQuestionMixArray[z]] = m_strTerm[x];
				for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
				{
					m_strAnswers[m_nQuestionMixArray[z]][m_nAnswerMixArray[m_nQuestionMixArray[z]][y]] = m_strTermDefinition[m_nMixArray[y]];
					m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strTermDefinition[x];
				}
				break;
			case 3:
				if(m_n5050SplitMixArray[x] == 0)
				{
					m_strQuestion[m_nQuestionMixArray[z]] = m_strTerm[x];
					for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
					{
						m_strAnswers[m_nQuestionMixArray[z]][m_nAnswerMixArray[m_nQuestionMixArray[z]][y]] = m_strTermDefinition[m_nMixArray[y]];
						m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strTermDefinition[x];
					}
				}
				else
				{
					m_strQuestion[m_nQuestionMixArray[z]] = m_strTermDefinition[x];
					for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
					{
						m_strAnswers[m_nQuestionMixArray[z]][m_nAnswerMixArray[m_nQuestionMixArray[z]][y]] = m_strTerm[m_nMixArray[y]];
						m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strTerm[x];
					}
				}
				break;
			}
			m_strTemp.Format(L"%s: %s", m_strTerm[x], m_strTermDefinition[x]);
			m_strExplanation[m_nQuestionMixArray[z]] = m_strTemp;
			z++;
		}
	}
	// Assign multiple choice questions to global matrix
	if(m_nNumberOfMC != 0)
	{
		for(x = 0; x <= m_nNumberOfMC; x++)
		{
			m_strQuestion[m_nQuestionMixArray[z]] = m_strMCQuestion[x];
			m_nImageFlag[m_nQuestionMixArray[z]] = m_nMCImageFlag[x];
			m_strImageName[m_nQuestionMixArray[z]] = m_strMCImageName[x];
			m_nNumberOfAnswers[m_nQuestionMixArray[z]] = 3;
			RandomMaker(m_nNumberOfAnswers[m_nQuestionMixArray[z]], m_nNumberOfAnswers[m_nQuestionMixArray[x]], -1);
			for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
			{
				m_nAnswerMixArray[m_nQuestionMixArray[z]][y] = m_nMixArray[y];
			}
			m_nMixArrayMaxLimit = m_nNumberOfMCAnswers[x];
			m_nMixArrayUpperLimit = m_nNumberOfAnswers[m_nQuestionMixArray[z]];
			m_nMixArrayKeyNumber = 0;
			RandomMaker(m_nMixArrayMaxLimit, m_nMixArrayUpperLimit, m_nMixArrayKeyNumber);
			for(y = 0; y <= m_nNumberOfAnswers[m_nQuestionMixArray[z]]; y++)
			{
				m_strAnswers[m_nQuestionMixArray[z]][m_nAnswerMixArray[m_nQuestionMixArray[z]][y]] = m_strMCAnswers[x][m_nMixArray[y]];
			}
			m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strMCAnswers[x][0];
			m_strExplanation[m_nQuestionMixArray[z]] = m_strMCExplanation[x];
			z++;
		}
	}
	// Assign True or False questions to global matrix
	if(m_nNumberOfTF != 0)
	{
		for(x = 0; x <= m_nNumberOfTF; x++)
		{
			m_strQuestion[m_nQuestionMixArray[z]] = m_strTFQuestion[x];
			m_nImageFlag[m_nQuestionMixArray[z]] = m_nTFImageFlag[x];
			m_strImageName[m_nQuestionMixArray[z]] = m_strTFImageName[x];
			m_nNumberOfAnswers[m_nQuestionMixArray[z]] = 1;
			// The first choice displayed is always True
			m_strAnswers[m_nQuestionMixArray[z]][0] = "True.";
			m_strAnswers[m_nQuestionMixArray[z]][1] = "False.";
			m_strCorrectAnswer[m_nQuestionMixArray[z]] = m_strTFAnswer[x];
			m_strExplanation[m_nQuestionMixArray[z]] = m_strTFExplanation[x];
			z++;
		}
	}
	return(true);
}

CString CTMDlg::ReadStringU(CFile &m_fileUnicodeFile)
{
	// Usage: CString = ReadStringU(Handle to Open File)

	// Holds the number of bytes transferred. Resets to zero if EOF reached
	UINT m_nBytesTransfered;
	// Holds the character read from the file
	TCHAR m_cTempCharBuffer[1];
	// A sequential array to hold each character read from the file 
	TCHAR m_strTempStringBuffer[257];
	// Indicates the position of the sequential array
	int m_nArrayPosition = 0;
	if(m_fileUnicodeFile.GetPosition() == 0)
	{
		m_nBytesTransfered = m_fileUnicodeFile.Read(m_cTempCharBuffer, 2);
		// Make sure the file is a UTF-16 big-endian file by checking the first character, the byte order mark (BOM)
		if(m_cTempCharBuffer[0] != _T('\xfeff'))
		{
			// If the file is newly opened and the BOM does not equal FEFF, inform the user and return NULL to the function call
			// MessageBox(L"Not a Unicode file.");
			return NULL;
		}
	}

	// Loop until either a carriage return-line feed character is read or EOF is reached
	do
	{
		// Read a character and get the number of bytes transferred (2 = the beginning of the file)
		m_nBytesTransfered = m_fileUnicodeFile.Read(m_cTempCharBuffer, 2);
		// Assign the character a position in the sequential array
		m_strTempStringBuffer[m_nArrayPosition] = m_cTempCharBuffer[0];
		// If the characters for CR/LF are read, replace CR with a NULL character and return the string to the function call
		if(m_strTempStringBuffer[m_nArrayPosition - 1] == _T('\x000d') && m_strTempStringBuffer[m_nArrayPosition] == _T('\x000a'))
		{
			m_strTempStringBuffer[m_nArrayPosition - 1] = _T('\x0000');
			break;
		}
		m_nArrayPosition++;
	// If EOF is reached, the number of bytes transferred will equal zero and the function will stop reading characters
	}while(m_nBytesTransfered != 0);
	// If EOF is reached, replace the last character read with a NULL character (Because of the loop, the position moved one over the length of the final string)
	m_strTempStringBuffer[m_nArrayPosition - 1] = _T('\x0000');
	// Return the final string read from the file
	return m_strTempStringBuffer;
}

void CTMDlg::WriteStringU(CFile& m_fileUnicodeFile, TCHAR *m_strUnicodeString)
{
	// Usage = WriteStringU(Handle to opened file, CString.GetBuffer())

	// Holds the length of the string
	size_t m_nStringLength;
	// Holds the character to be written to the file
	TCHAR m_cTempCharBuffer[1];
	// If the file is newly opened, assign a BOM of FEFF to the first character written
	if(m_fileUnicodeFile.GetPosition() == 0)
	{
		m_cTempCharBuffer[0] = _T('\xfeff');
		m_fileUnicodeFile.Write(m_cTempCharBuffer, 2);
	}
	// Get the length of the string and double it by 2 in order to hold the Unicode characters
	m_nStringLength = (wcsnlen(m_strUnicodeString, 256)) * 2;
	// Write the string
	m_fileUnicodeFile.Write(m_strUnicodeString, (UINT) m_nStringLength);
	// Finish the string with the characters for carraige return and line feed
	m_cTempCharBuffer[0] = _T('\x000d');
	m_fileUnicodeFile.Write(m_cTempCharBuffer, 2);
	m_cTempCharBuffer[0] = _T('\x000a');
	m_fileUnicodeFile.Write(m_cTempCharBuffer, 2);
}

CString CTMDlg::Crypt(TCHAR *m_strInput, size_t m_nInputLength, TCHAR *m_strKey, size_t m_nKeyLength)
{
    //Usage = m_strDecryptedText = Crypt(m_strTextToEncrypt.GetBuffer(), _tcslen(m_strTextToEncrypt), m_strKey.GetBuffer(), _tcslen(m_strKey));

	//we will consider size of m_strKeyBuffer 256 bytes (extra byte are only to prevent any mishap just in case)
    TCHAR m_strKeyBuffer[257], m_strKeyBuffer2[257];
    unsigned long m, n, o, p;

    //this unsecured key is to be used only when there is no input key from user
    static const TCHAR OurUnSecuredKey[] = L"Test Mate® Program";
    static const size_t OurKeyLen = _tcslen(OurUnSecuredKey);    
    TCHAR temp, l;
    m = n = o = p = 0;
    temp = 0;

    //always initialize the arrays with zero
    ZeroMemory(m_strKeyBuffer, sizeof(m_strKeyBuffer));
    ZeroMemory(m_strKeyBuffer2, sizeof(m_strKeyBuffer2));

    //initialize m_strKeyBuffer m
    for(m = 0; m < 256U; m++)
    {
        m_strKeyBuffer[m] = (TCHAR)m;
    }

	n = 0;
    //whether user has sent any input key
    if(m_nKeyLength)
    {
        //initialize the m_strKeyBuffer2 with user key
        for(m = 0; m < 256U; m++)
        {
            if(n == m_nKeyLength)
            {
                n = 0;
            }
            m_strKeyBuffer2[m] = (TCHAR)(((int)m_strKey[n++]) + m_nAddValuePerLine);
        }    
    }
    else
    {
        //initialize the m_strKeyBuffer2 with our key
        for(m = 0; m < 256U; m++)
        {
            if(n == OurKeyLen)
            {
                n = 0;
            }
            m_strKeyBuffer2[m] = (TCHAR)(((int)OurUnSecuredKey[n++]) + m_nAddValuePerLine);
        }
    }

    n = 0 ; //Initialize n
    //scramble m_strKeyBuffer1 with m_strKeyBuffer2
    for(m = 0; m < 256; m++)
    {
        n = (n + (unsigned long) m_strKeyBuffer[m] + (unsigned long) m_strKeyBuffer2[m]) % 256U;
        temp =  m_strKeyBuffer[m];                    
        m_strKeyBuffer[m] = m_strKeyBuffer[n];
        m_strKeyBuffer[n] =  temp;
    }

    m = n = 0;
    for(p = 0; p < m_nInputLength; p++)
    {
        //increment m
        m = (m + 1U) % 256U;
        //increment n
        n = (n + (unsigned long) m_strKeyBuffer[m]) % 256U;

        //Scramble m_strKeyBuffer #1 further so encryption routine will
        //will repeat itself at great interval
        temp = m_strKeyBuffer[m];
        m_strKeyBuffer[m] = m_strKeyBuffer[n];
        m_strKeyBuffer[n] = temp;

        //Get ready to create pseudo random  byte for encryption key
        o = ((unsigned long) m_strKeyBuffer[m] + (unsigned long) m_strKeyBuffer[n]) %  256U;

        //get the random byte
        l = m_strKeyBuffer[o];

		//xor with the data and done
		//m_strInput[p] = ( m_strInput[p] ^ l );

		if (((m_strInput[p] ^ l) > _T('\x001F')) && ((m_strInput[p] ^ l) != _T('\x007F')))
		{
			m_strInput[p] = m_strInput[p] ^ l;
		}
		else
		{
			m_strInput[p] = m_strInput[p];
		}
		//XOR is done only if the result is not a NULL
    }
	if(m_nAddValuePerLine != 3)
	{
		m_nAddValuePerLine++;
	}
	else
	{
		m_nAddValuePerLine = 0;
	}
	return m_strInput;
}

void CTMDlg::RandomMaker(int m_nMixArrayMaxLimit, int m_nMixArrayUpperLimit, int m_nMixArrayKeyNumber)
{
	int r = 0;
	int m = 0;
	int n = 0;
	int i = 0;
	// Check if there is a number that must appear
	if(m_nMixArrayKeyNumber != -1)
	{
		m_nMixArray[0] = m_nMixArrayKeyNumber;
		m = 1;
	}
	for(n = m; n <= m_nMixArrayUpperLimit; n++)
	{
GENERATE:
		// Make sure that no numbers less than the key number are generated as long as the key number is four less than the limit
		if(m_nMixArrayKeyNumber != -1 && m_nMixArrayKeyNumber < (m_nMixArrayMaxLimit - 4))
		{
			r = getrandom(m_nMixArrayKeyNumber + 1, m_nMixArrayMaxLimit);
		}
		// If the key number is greater than the limit minus 4
		if(m_nMixArrayKeyNumber != -1 && m_nMixArrayKeyNumber >= (m_nMixArrayMaxLimit - 4))
		{
			r = getrandom(1, m_nMixArrayMaxLimit);
		}
		// If no key number must appear (-1)
		if(m_nMixArrayKeyNumber == -1)
		{
			r = getrandom(0, m_nMixArrayMaxLimit);
		}
		// If a generated number is equal to the key number, generate another number
		if(m_nMixArrayKeyNumber != -1 && r == m_nMixArrayKeyNumber)
		{
			goto GENERATE;
		}
		for(i = m; i < n; i++)
		{
			if(m_nMixArray[i] == r)
			{
				goto GENERATE;
			}
		}
		m_nMixArray[n] = r;
	}
	return;
}

void CTMDlg::ResetTest(void)
{
	m_nCount = 0;
	m_nTrueCount = 0;
	m_bEnableRadio = true;
	m_bJustStartedFlag = false;
	m_nNumberCorrect = 0;
	m_bTestCompleteFlag = false;
	m_nScoreCount = 0;
	m_tStartTime = CTime::GetCurrentTime();
	PrepScreen();
}

void CTMDlg::PrepScreen(void)
{
	if(m_nCount < m_nTrueCount)
	{
		m_bEnableRadio = false;
		GetDlgItem(IDC_NEXTBUTTON)->EnableWindow(true);
	}
	if(m_nCount == m_nTrueCount && m_bTestCompleteFlag == false)
	{
		m_bEnableRadio = true;
		GetDlgItem(IDC_NEXTBUTTON)->EnableWindow(true);
		GetDlgItem(IDC_REVIEWBUTTON)->EnableWindow(true);
	}
	if(m_nCount == m_nTrueCount && m_bTestCompleteFlag == true)
	{
		m_bEnableRadio = false;
	}
	GetDlgItem(IDC_STATIC_TESTTITLE)->SetWindowText(m_strTestTitle);
	if(g_pDlgImageDlg)
	{
		delete g_pDlgImageDlg;
		g_pDlgImageDlg = NULL;
	}
	m_strStaticQuestionCounter.Format(L"%d of %d", m_nCount + 1, m_nNumberOfQuestions + 1);
	GetDlgItem(IDC_STATIC_QUESTIONCOUNTER)->SetWindowText(m_strStaticQuestionCounter);
	GetDlgItem(IDC_STATIC_QUESTIONBOX)->SetWindowText(m_strQuestion[m_nCount]);
	switch(m_nNumberOfAnswers[m_nCount])
	{
	case 0:
		GetDlgItem(IDC_RADIO1)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO1)->SetWindowText(m_strAnswers[m_nCount][0]);
			GetDlgItem(IDC_RADIO1)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO2)->ShowWindow(false);
		GetDlgItem(IDC_RADIO3)->ShowWindow(false);
		GetDlgItem(IDC_RADIO4)->ShowWindow(false);
		break;
	case 1:
		GetDlgItem(IDC_RADIO1)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO1)->SetWindowText(m_strAnswers[m_nCount][0]);
			GetDlgItem(IDC_RADIO1)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO2)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO2)->SetWindowText(m_strAnswers[m_nCount][1]);
			GetDlgItem(IDC_RADIO2)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO3)->ShowWindow(false);
		GetDlgItem(IDC_RADIO4)->ShowWindow(false);
		break;
	case 2:
		GetDlgItem(IDC_RADIO1)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO1)->SetWindowText(m_strAnswers[m_nCount][0]);
			GetDlgItem(IDC_RADIO1)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO2)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO2)->SetWindowText(m_strAnswers[m_nCount][1]);
			GetDlgItem(IDC_RADIO2)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO3)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO3, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO3)->SetWindowText(m_strAnswers[m_nCount][2]);
			GetDlgItem(IDC_RADIO3)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO4)->ShowWindow(false);
		break;
	case 3:
		GetDlgItem(IDC_RADIO1)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO1)->SetWindowText(m_strAnswers[m_nCount][0]);
			GetDlgItem(IDC_RADIO1)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO2)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO2)->SetWindowText(m_strAnswers[m_nCount][1]);
			GetDlgItem(IDC_RADIO2)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO3)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO3, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO3)->SetWindowText(m_strAnswers[m_nCount][2]);
			GetDlgItem(IDC_RADIO3)->EnableWindow(m_bEnableRadio);
		GetDlgItem(IDC_RADIO4)->ShowWindow(true);
			CheckDlgButton(IDC_RADIO4, BST_UNCHECKED);
			GetDlgItem(IDC_RADIO4)->SetWindowText(m_strAnswers[m_nCount][3]);
			GetDlgItem(IDC_RADIO4)->EnableWindow(m_bEnableRadio);
		break;
	}
	m_strRadioTextSelected[m_nCount] = "Nothing Selected";
	if(m_nImageFlag[m_nCount] == 1)
	{
		if(!g_pDlgImageDlg)
		{
			g_pDlgImageDlg = new CImageDlg(this);
//			g_pDlgImageDlg->SetWindowText(m_strTestTitle);
			g_pDlgImageDlg->m_strPopUpImage.SetBitmap((HBITMAP)::LoadImage(AfxGetInstanceHandle(), m_strImageName[m_nCount], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		}
	}
}

void CTMDlg::EnableScreen(void)
{
	GetDlgItem(IDC_STATIC_CLOCK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TESTTITLE)->EnableWindow(true);
	GetDlgItem(IDC_STATIC_QUESTIONCOUNTER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_QUESTIONBOX)->EnableWindow(true);
	GetDlgItem(IDC_RADIO1)->EnableWindow(true);
	GetDlgItem(IDC_RADIO2)->EnableWindow(true);
	GetDlgItem(IDC_RADIO3)->EnableWindow(true);
	GetDlgItem(IDC_RADIO4)->EnableWindow(true);
	GetDlgItem(IDC_REVIEWBUTTON)->EnableWindow(false);
	if(m_nProvideFeedbackToggle == 0)
	{
		GetDlgItem(IDC_SHOW_SCORE)->EnableWindow(false);
	}
	if(m_nProvideFeedbackToggle == 1)
	{
		GetDlgItem(IDC_SHOW_SCORE)->EnableWindow(true);
	}
	GetDlgItem(IDC_NEXTBUTTON)->EnableWindow(true);
}


void CTMDlg::OnMainSaveTheCurrentTest(void)
{
	if(m_bJustStartedFlag == true)
	{
		MessageBox(L"There is no open test to save.", L"Test Mate", MB_ICONINFORMATION);
		return;
	}
	CStdioFile m_fileOpenDataBase;
	int x;
	int y;
	CString m_strSaveFile;
	CString m_strEncryptedText;
	CFileDialog FileDlg(FALSE, L"tsv", L"*.tsv", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Saved Test Mate Test (*.tsv)|*.tsv||");
	FileDlg.m_ofn.lpstrInitialDir = L"\\tm";
	m_nAddValuePerLine = 0;
	if(FileDlg.DoModal() == IDOK)
	{
		// If no test is open or the user does anything except click on "No", attempt to open a database
		m_strSaveFile = FileDlg.GetPathName();
		if(!m_fileOpenDataBase.Open(m_strSaveFile, CFile::modeCreate | CFile::modeWrite))
		{
			MessageBox(L"Test Mate cannot create the save file.", L"Test Mate", MB_ICONERROR);
			return;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;

			// Usage = m_strDecryptedText = Crypt(m_strTextToDecrypt.GetBuffer(), _tcslen(m_strTextToDecrypt), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Old: m_fileOpenDataBase.WriteString(m_strTemp);

			z = getrandom(1, 3);
			switch(z)
			{
			case 1:
				z = 1010100;
				break;
			case 2:
				z = 1001101;
				break;
			case 3:
				z = 1011000;
				break;
			}
			m_strTemp.Format(L"%d", z);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());
			
			m_strTemp.Format(L"%s", m_strTestTitle);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%s", m_strFileName);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nAlwaysOnTopToggle);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));			
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nProvideFeedbackToggle);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nRandomizeQuestionOrderToggle);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nShowClockToggle);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nNumberOfQuestions);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nCount);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nTrueCount);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nNumberCorrect);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_nScoreCount);
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			m_strTemp.Format(L"%d", m_tElapsedTime.GetTotalSeconds());
			m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_strTemp.Format(L"%s", m_strEncryptedText);
			WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

			for(x = 0; x <= m_nNumberOfQuestions; x++)
			{
				m_strTemp.Format(L"%s", m_strQuestion[x]);
				m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_strTemp.Format(L"%s", m_strEncryptedText);
				WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

				m_strTemp.Format(L"%d", m_nImageFlag[x]);
				m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_strTemp.Format(L"%s", m_strEncryptedText);
				WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

				if(m_nImageFlag[x] == 1)
				{
					m_strTemp.Format(L"%s", m_strImageName[x]);
					m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
					m_strTemp.Format(L"%s", m_strEncryptedText);
					WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());
				}

				m_strTemp.Format(L"%d", m_nNumberOfAnswers[x]);
				m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_strTemp.Format(L"%s", m_strEncryptedText);
				WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

				for(y= 0; y <= m_nNumberOfAnswers[x]; y++)
				{
					m_strTemp.Format(L"%s", m_strAnswers[x][y]);
					m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
					m_strTemp.Format(L"%s", m_strEncryptedText);
					WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());
				}

				m_strTemp.Format(L"%s", m_strCorrectAnswer[x]);
				m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_strTemp.Format(L"%s", m_strEncryptedText);
				WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());

				m_strTemp.Format(L"%s", m_strExplanation[x]);
				m_strEncryptedText = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_strTemp.Format(L"%s", m_strEncryptedText);
				WriteStringU(m_fileOpenDataBase, m_strTemp.GetBuffer());
			}
			m_fileOpenDataBase.Close();
			return;
		}
	}
	else
		return;
}

void CTMDlg::OnMainLoadAPreviousTest(void)
{
	CStdioFile m_fileOpenDataBase;
	int x;
	int y;
	CString m_strEncryptedText;
	int m_nSavedTime;
	CFileDialog FileDlg(TRUE, L"tsv", L"*.tsv", 0, L"Saved Test Mate Test (*.tsv)|*.tsv||");
	FileDlg.m_ofn.lpstrInitialDir = L"\\tm";
	m_nAddValuePerLine = 0;
	if(FileDlg.DoModal() == IDOK)
	{
		// If no test is open or the user does anything except click on "No", attempt to open a database
		m_strFileName = FileDlg.GetPathName();
		if(!m_fileOpenDataBase.Open(m_strFileName, CFile::modeRead))
		{
			MessageBox(L"Test Mate cannot open the specified file.", L"Test Mate", MB_ICONERROR);
			return;
		}
		else
		{
			x = 0;
			y = 0;
			// Old: m_fileOpenDataBase.Open(FileDlg.GetFileName(), CFile::modeRead);

			// Usage = m_strDecryptedText = Crypt(m_strTextToDecrypt.GetBuffer(), _tcslen(m_strTextToDecrypt), m_strKey.GetBuffer(), _tcslen(m_strKey));
			// Old: m_fileOpenDataBase.ReadString(m_strEncryptedText);
			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			if(_ttoi(m_strTemp) != 1010100 && _ttoi(m_strTemp) != 1001101 && _ttoi(m_strTemp) != 1011000)
			{
				m_fileOpenDataBase.Close();
				MessageBox(L"Invalid saved test.", L"Test Mate", MB_ICONERROR);
				return;
			}

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTestTitle = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strFileName = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nAlwaysOnTopToggle = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nProvideFeedbackToggle = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nRandomizeQuestionOrderToggle = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nShowClockToggle = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nNumberOfQuestions = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nCount = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nTrueCount = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nNumberCorrect = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nScoreCount = _ttoi(m_strTemp);

			m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
			m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			m_nSavedTime = _ttoi(m_strTemp);

			for(x = 0; x <= m_nNumberOfQuestions; x++)
			{
				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strQuestion[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));

				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_nImageFlag[x] = _ttoi(m_strTemp);

				if(m_nImageFlag[x] == 1)
				{
					m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
					m_strImageName[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
				}

				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strTemp = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
				m_nNumberOfAnswers[x] = _ttoi(m_strTemp);

				for(y= 0; y <= m_nNumberOfAnswers[x]; y++)
				{
					m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
					m_strAnswers[x][y] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
				}

				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strCorrectAnswer[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));

				m_strEncryptedText = ReadStringU(m_fileOpenDataBase);
				m_strExplanation[x] = Crypt(m_strEncryptedText.GetBuffer(), _tcslen(m_strEncryptedText), m_strKey.GetBuffer(), _tcslen(m_strKey));
			}
			m_fileOpenDataBase.Close();
			m_bJustStartedFlag = false;
			m_bTestCompleteFlag = false;
			m_bEnableRadio = true;
			m_nRadioButtonSelected = -1;
			m_tStartTime = CTime::GetCurrentTime();
			m_tStartTime -= m_nSavedTime;
			EnableScreen();
			PrepScreen();
			UpdateData(false);
			return;
		}
	}
	else
		return;
}

void CTMDlg::OnOptionsAlwaysOnTop(void)
{
	m_nAlwaysOnTopToggle = m_nAlwaysOnTopToggle == 0 ? 1 : 0;
	if(m_nAlwaysOnTopToggle == 0)
		this->SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		this->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void CTMDlg::OnUpdateOptionsAlwaysOnTop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_nAlwaysOnTopToggle);
}

void CTMDlg::OnOptionsProvideFeedback(void)
{
	if(m_bJustStartedFlag == false && m_bTestCompleteFlag == false)
	{
		m_nProvideFeedbackToggle = m_nProvideFeedbackToggle == 0 ? 1 : 0;
		if((MessageBox(L"This will restart the current module. Do you wish to continue?", L"Test Mate", MB_YESNO | MB_ICONQUESTION)) == IDYES)
		{
			if(OpenFile() == true)
			{
				ResetTest();
				EnableScreen();
				return;
			}
			else
			{
				m_nProvideFeedbackToggle = m_nProvideFeedbackToggle == 0 ? 1 : 0;
				MessageBox(L"Test Mate cannot open the specified file.", L"Test Mate", MB_ICONERROR);
				return;
			}
		}
		else
			return;
	}
	else
		m_nProvideFeedbackToggle = m_nProvideFeedbackToggle == 0 ? 1 : 0;
}

void CTMDlg::OnUpdateOptionsProvideFeedback(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_nProvideFeedbackToggle);
}

void CTMDlg::OnOptionsRandomizeQuestionOrder(void)
{
	if(m_bJustStartedFlag == false && m_bTestCompleteFlag == false)
	{
		if((MessageBox(L"This will restart the current module. Do you wish to continue?", L"Test Mate", MB_YESNO | MB_ICONQUESTION)) == IDYES)
		{
			m_nRandomizeQuestionOrderToggle = m_nRandomizeQuestionOrderToggle == 0 ? 1 : 0;
			if(OpenFile() == true)
			{
				ResetTest();
				EnableScreen();
				return;
			}
			else
			{
				m_nRandomizeQuestionOrderToggle = m_nRandomizeQuestionOrderToggle == 0 ? 1 : 0;
				MessageBox(L"Test Mate cannot open the specified file.", L"Test Mate", MB_ICONERROR);
				return;
			}
		}
		else
			return;
	}
	else
		m_nRandomizeQuestionOrderToggle = m_nRandomizeQuestionOrderToggle == 0 ? 1 : 0;
}

void CTMDlg::OnUpdateOptionsRandomizeQuestionOrder(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_nRandomizeQuestionOrderToggle);
}

void CTMDlg::OnOptionsShowClock(void)
{
	m_nShowClockToggle = m_nShowClockToggle == 0 ? 1 : 0;
	BOOL bVisible = GetDlgItem(IDC_STATIC_CLOCK)->IsWindowVisible();
	GetDlgItem(IDC_STATIC_CLOCK)->ShowWindow(bVisible ? SW_HIDE : SW_SHOW);
}

void CTMDlg::OnUpdateOptionsShowClock(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_nShowClockToggle);
}

void CTMDlg::OnFileExitTestMate(void)
{
	if((MessageBox(L"Are you sure you want to quit?", L"Test Mate", MB_YESNO | MB_ICONEXCLAMATION)) == IDYES)
		exit(0);
	else
		return;
}

void CTMDlg::OnHelpAboutTestMate(void)
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTMDlg::OnBnClickedReviewButton(void)
{
	if(m_nCount > 0)
	{
		m_nCount--;
		PrepScreen();
	}
	else
	{
		MessageBox(L"This is the beginning of the test.", L"Test Mate", MB_ICONEXCLAMATION);
	}
}

void CTMDlg::OnBnClickedShowScore(void)
{
	int pct;
	if(m_nScoreCount == 0 || m_nNumberCorrect == 0)
	{
		pct = 0;
		m_strTemp.Format(L"Your score: %d percent (%d correct out of %d).", pct, m_nNumberCorrect, m_nScoreCount);
		MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		pct = (m_nNumberCorrect * 100) / (m_nScoreCount);
		m_strTemp.Format(L"Your score: %d percent (%d correct out of %d).", pct, m_nNumberCorrect, m_nScoreCount);
		MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
	}
}

void CTMDlg::OnBnClickedNextButton(void)
{
	UpdateData(true);
	if(m_nCount < m_nTrueCount)
	{
		m_nCount++;
		PrepScreen();
		return;
	}
	switch(m_nRadioButtonSelected)
	{
	case 0:
		GetDlgItem(IDC_RADIO1)->GetWindowText(m_strRadioTextSelected[m_nCount]);
		break;
	case 1:
		GetDlgItem(IDC_RADIO2)->GetWindowText(m_strRadioTextSelected[m_nCount]);
		break;
	case 2:
		GetDlgItem(IDC_RADIO3)->GetWindowText(m_strRadioTextSelected[m_nCount]);
		break;
	case 3:
		GetDlgItem(IDC_RADIO4)->GetWindowText(m_strRadioTextSelected[m_nCount]);
		break;
	default:
		m_strRadioTextSelected[m_nCount] == "Nothing Selected";
		break;
	}
	m_nRadioButtonSelected = -1;
	UpdateData(false);
	if(m_bTestCompleteFlag == true)
	{
		if(m_nCount >= 0 && m_nCount < m_nNumberOfQuestions)
		{
			m_nCount++;
			m_nTrueCount++;
			PrepScreen();
		}
		else if(m_nCount == m_nNumberOfQuestions)
		{
			GetDlgItem(IDC_NEXTBUTTON)->EnableWindow(false);
			MessageBox(L"This is the end of your test. Please select 'Start New Test...' to load a new test, 'Review' to review this test or 'Exit Test Mate' to end the program.", L"Test Mate", MB_ICONEXCLAMATION);
		}
	}
	else if(m_bTestCompleteFlag == false)
	{
		if(m_strRadioTextSelected[m_nCount] == "Nothing Selected")
		{
			MessageBox(L"Please select an answer.", L"Test Mate", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		else if(m_nCount >= 0 && m_nCount < m_nNumberOfQuestions)
		{
			m_nScoreCount++;
			if(m_strRadioTextSelected[m_nCount] == m_strCorrectAnswer[m_nCount])
			{
				m_nNumberCorrect++;
				if(m_nProvideFeedbackToggle == 1)
				{
					m_strTemp.Format(L"Correct. %s", m_strExplanation[m_nCount]);
					MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
				}
			}
			else
			{
				if(m_nProvideFeedbackToggle == 1)
				{
					m_strTemp.Format(L"Incorrect. %s", m_strExplanation[m_nCount]);
					MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONERROR);
				}
			}
			m_nCount++;
			m_nTrueCount++;
			PrepScreen();
		}
		else if(m_nCount == m_nNumberOfQuestions)
		{
			m_nScoreCount++;
			GetDlgItem(IDC_NEXTBUTTON)->EnableWindow(false);
			GetDlgItem(IDC_RADIO1)->EnableWindow(false);
			GetDlgItem(IDC_RADIO2)->EnableWindow(false);
			GetDlgItem(IDC_RADIO3)->EnableWindow(false);
			GetDlgItem(IDC_RADIO4)->EnableWindow(false);
			GetDlgItem(IDC_STATIC_QUESTIONBOX)->EnableWindow(false);
			m_bTestCompleteFlag = true;
			if(m_strRadioTextSelected[m_nCount] == m_strCorrectAnswer[m_nCount])
			{
				m_nNumberCorrect++;
				if(m_nProvideFeedbackToggle == 1)
				{
					m_strTemp.Format(L"Correct. %s", m_strExplanation[m_nCount]);
					MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
				}
			}
			else
			{
				if(m_nProvideFeedbackToggle == 1)
				{
					m_strTemp.Format(L"Incorrect. %s", m_strExplanation[m_nCount]);
					MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONERROR);
				}
			}
			int pct;
			if(m_nScoreCount == 0 || m_nNumberCorrect == 0)
			{
				pct = 0;
				m_strTemp.Format(L"Your score: %d percent (%d correct out of %d).", pct, m_nNumberCorrect, m_nScoreCount);
				MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				pct = (m_nNumberCorrect * 100) / (m_nScoreCount);
				m_strTemp.Format(L"Your score: %d percent (%d correct out of %d).", pct, m_nNumberCorrect, m_nScoreCount);
				MessageBox(m_strTemp, L"Test Mate", MB_OK | MB_ICONINFORMATION);
			}
			MessageBox(L"This is the end of the test.", L"Test Mate", MB_ICONEXCLAMATION);
		}
	}
}

void CTMDlg::OnTimer(UINT nIDEvent)
{
	CTime m_tCurrentTime;
	if(m_bTestCompleteFlag == false)
	{
		m_tCurrentTime = CTime::GetCurrentTime();
		m_tElapsedTime = m_tCurrentTime - m_tStartTime;
		m_strStaticClock.Format(L"%02d:%02d:%02d", m_tElapsedTime.GetHours(), m_tElapsedTime.GetMinutes(), m_tElapsedTime.GetSeconds());
		GetDlgItem(IDC_STATIC_CLOCK)->SetWindowText(m_strStaticClock);
	}
}

void CTMDlg::OnOK(void)
{
}

void CTMDlg::OnCancel(void)
{
	if((MessageBox(L"Are you sure you want to quit?", L"Test Mate", MB_YESNO | MB_ICONEXCLAMATION)) == IDYES)
		exit(0);
	else
		return;
}

void CTMDlg::OnHelp(void)
{
	if((int)(ShellExecute(NULL, L"open", L"\\TM\\Test Mate User Guide.mht", NULL, NULL, SW_SHOWNORMAL)) <= 32)
	{
		MessageBox(L"Test Mate is unable to open the help file.\n\nPlease contact us at test_mate@shorens.com.", L"Test Mate", MB_ICONERROR);
	}
}

void CTMDlg::OnHelpALetterToAllServiceMembers()
{
	if((int)(ShellExecute(NULL, L"open", L"\\TM\\SM Letter.mht", NULL, NULL, SW_SHOWNORMAL)) <= 32)
	{
		MessageBox(L"Test Mate is unable to open the file.\n\nPlease contact us at test_mate@shorens.com.", L"Test Mate", MB_ICONERROR);
	}
}
