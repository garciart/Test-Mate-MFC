#pragma once
#include "afxwin.h"


// CImageDlg dialog

class CImageDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageDlg)

public:
	CImageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageDlg();

// Dialog Data
	enum { IDD = IDD_IMAGEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_strPopUpImage;
	void CImageDlg::OnOK();
	void CImageDlg::OnCancel();
};
