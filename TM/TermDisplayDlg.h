#pragma once


// TermDisplayDlg dialog

class TermDisplayDlg : public CDialog
{
	DECLARE_DYNAMIC(TermDisplayDlg)

public:
	TermDisplayDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TermDisplayDlg();

// Dialog Data
	enum { IDD = IDD_TERMS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	int m_nChoiceFlag;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedTerms();
	afx_msg void OnBnClickedDefinitions();
	afx_msg void OnBnClickedRandomchoice();
	afx_msg void TermDisplayDlg::OnCancel();
};
