#pragma once
#include "afxwin.h"
#include "stdafx.h"

// CLoginDlg dialog

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg(void);

// Dialog Data
	enum { IDD = IDD_LOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void);
	CBrush *m_brush;
	DECLARE_MESSAGE_MAP()
public:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void CLoginDlg::OnEnChangeUsername(void);
		CString m_strUserName;
	afx_msg void CLoginDlg::OnBnClickedOk(void);
		int m_nAddValuePerLine;
		CString m_strKey;
		CString m_strPassword;
		CEdit m_editUserName;
		int m_nLoginAttempts;
	afx_msg CString CLoginDlg::ReadStringU(CFile& m_fileUnicodeFile);
	afx_msg CString CLoginDlg::Crypt(TCHAR *m_strInput, size_t m_nInputLength, TCHAR *m_strKey, size_t m_nKeyLength);
	afx_msg void OnEnChangePassword();
};
