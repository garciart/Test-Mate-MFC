// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TM.h"
#include "LoginDlg.h"
#include ".\logindlg.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_strUserName(_T(""))
	, m_nAddValuePerLine(0)
	, m_strKey(_T(""))
	, m_strPassword(_T(""))
	, m_nLoginAttempts(0)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 20);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 8);
	DDX_Control(pDX, IDC_USERNAME, m_editUserName);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_USERNAME, OnEnChangeUsername)
	ON_EN_CHANGE(IDC_PASSWORD, &CLoginDlg::OnEnChangePassword)
END_MESSAGE_MAP()

// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush = new CBrush(RGB(255, 255, 255));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkColor(RGB(255, 255, 255));
	return (HBRUSH)(m_brush->GetSafeHandle());
}

void CLoginDlg::OnEnChangeUsername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData();
	if(m_strUserName != "")
	{
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(true);
		GetDlgItem(IDC_PASSWORD)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(false);
		GetDlgItem(IDC_PASSWORD)->EnableWindow(false);
	}
}

void CLoginDlg::OnEnChangePassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData();
	if(m_strPassword != "")
	{
		GetDlgItem(IDOK)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(false);
	}
}

void CLoginDlg::OnBnClickedOk()
{
	CStdioFile m_fileOpenProfile;
	CString m_strUserNameFromFile;
	CString m_strPasswordFromFile;
	CString m_strTemp;
	UpdateData();
	if(m_nLoginAttempts <= 0 || m_nLoginAttempts > 3)
		m_nLoginAttempts = 1;
	m_nAddValuePerLine = 0;
	if((m_fileOpenProfile.Open(L"\\tm\\tm.pfl", CFile::modeRead)) == false)
	{
		MessageBox(L"Cannot open your profile.  Please contact us as at test_mate@shorens.com soon as possible.", L"Test Mate", MB_ICONERROR);
		exit(0);
	}
	// Usage: CString = ReadStringU(Handle to Open File)
	// Old: m_fileOpenProfile.ReadString(m_strUserNameFromFile);
	m_strUserNameFromFile = ReadStringU(m_fileOpenProfile);
	// Old: m_fileOpenProfile.ReadString(m_strPasswordFromFile);
	m_strPasswordFromFile = ReadStringU(m_fileOpenProfile);

	m_fileOpenProfile.Close();

	m_strKey = L"Test Mate™ Program";
	m_strTemp = m_strUserNameFromFile;
	m_strUserNameFromFile = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));
	m_strTemp = m_strPasswordFromFile;
	m_strPasswordFromFile = Crypt(m_strTemp.GetBuffer(), _tcslen(m_strTemp), m_strKey.GetBuffer(), _tcslen(m_strKey));

	if((m_strUserName == m_strUserNameFromFile) && (m_strPassword == m_strPasswordFromFile))
	{
		COleDateTime m_dateCurrent;
		m_dateCurrent = COleDateTime::GetCurrentTime();
		int m_nDay;
		int m_nRemainingDays;
		if(m_dateCurrent.GetYear() == 2009)
		{
			m_nDay = m_dateCurrent.GetDayOfYear();
			m_nRemainingDays = 90 - m_nDay;
		}
		else
		{
			m_nDay = m_dateCurrent.GetDayOfYear();
			m_nRemainingDays = (365 - m_nDay) + 90;
		}
		if(m_nRemainingDays <= 30)
		{
            m_strTemp.Format(L"Welcome to Test Mate!\n\nRemember, this evaluation version will expire in %d more day(s).\n\nPlease contact us at test_mate@shorens.com as soon as possible.", m_nRemainingDays);
			MessageBox(m_strTemp, L"Login Successful", MB_ICONERROR);
		}
		else
		{
            m_strTemp.Format(L"Welcome!\n\nThis is an evaluation version of Test Mate.\n\nThe final version will be free for all servicemembers.\n\nThere are %d days remaining in your evaluation period.\n\nIf you encounter any problems, please contact us at test_mate@shorens.com.", m_nRemainingDays);
			MessageBox(m_strTemp, L"Login Successful", MB_ICONINFORMATION);
		}
		OnOK();
	}
	else
	{
		if((m_nLoginAttempts++) == 3)
		{
			MessageBox(L"You seem to have forgotten your login information.\n\nPlease contact us at test_mate@shorens.com as soon as possible.", L"Test Mate", MB_ICONERROR);
			exit(0);
		}
		MessageBox(L"Invalid login attempt.", L"Test Mate", MB_ICONWARNING);
		m_strUserName = "";
		m_strPassword = "";
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(false);
		GetDlgItem(IDC_PASSWORD)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(false);
		this->m_editUserName.SetFocus();
		UpdateData(false);
		return;
	}
}

CString CLoginDlg::ReadStringU(CFile &m_fileUnicodeFile)
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
//			MessageBox(L"Not a Unicode file.");
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

CString CLoginDlg::Crypt(TCHAR *m_strInput, size_t m_nInputLength, TCHAR *m_strKey, size_t m_nKeyLength)
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
