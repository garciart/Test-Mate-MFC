// ImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TM.h"
#include "ImageDlg.h"
#include "TMDlg.h"

// CImageDlg dialog

IMPLEMENT_DYNAMIC(CImageDlg, CDialog)

BEGIN_MESSAGE_MAP(CImageDlg, CDialog)
END_MESSAGE_MAP()

// CImageDlg message handlers

CImageDlg::CImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageDlg::IDD, pParent)
{
	if(Create(CImageDlg::IDD,pParent))
	{
		ShowWindow(SW_SHOW);
	}
}

CImageDlg::~CImageDlg()
{
}

void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_strPopUpImage);
}

void CImageDlg::OnOK()
{
}

void CImageDlg::OnCancel()
{
}