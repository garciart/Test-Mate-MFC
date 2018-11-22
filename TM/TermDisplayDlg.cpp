// TermDisplayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TM.h"
#include "TMDlg.h"
#include "TermDisplayDlg.h"

// TermDisplayDlg dialog

IMPLEMENT_DYNAMIC(TermDisplayDlg, CDialog)

TermDisplayDlg::TermDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TermDisplayDlg::IDD, pParent)
	, m_nChoiceFlag(0)
{

}

TermDisplayDlg::~TermDisplayDlg()
{
}

void TermDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TermDisplayDlg, CDialog)
	ON_BN_CLICKED(IDC_TERMS, &TermDisplayDlg::OnBnClickedTerms)
	ON_BN_CLICKED(IDC_DEFINITIONS, &TermDisplayDlg::OnBnClickedDefinitions)
	ON_BN_CLICKED(IDC_RANDOMCHOICE, &TermDisplayDlg::OnBnClickedRandomchoice)
END_MESSAGE_MAP()


// TermDisplayDlg message handlers


void TermDisplayDlg::OnBnClickedTerms()
{
	m_nChoiceFlag = 1;
	OnOK();
}

void TermDisplayDlg::OnBnClickedDefinitions()
{
	m_nChoiceFlag = 2;
	OnOK();
}

void TermDisplayDlg::OnBnClickedRandomchoice()
{
	m_nChoiceFlag = 3;
	OnOK();
}

void TermDisplayDlg::OnCancel()
{
}
