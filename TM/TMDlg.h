// TMDlg.h : header file
//

#pragma once
#include "afxext.h"
#include "afxwin.h"


// CTMDlg dialog
class CTMDlg : public CDialog
{
// Construction
public:
	CTMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon; // system global

	// Generated message map functions
	virtual BOOL OnInitDialog(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint(void);
	afx_msg HCURSOR OnQueryDragIcon(void);
	CBrush *m_brush;
public:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void CTMDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void CTMDlg::OnFileStartNewTest(void);
		bool m_bJustStartedFlag;
		CString m_strFileName;
	afx_msg bool CTMDlg::OpenFile(void);
		int x;
		int y;
		int z;
		CString m_strTemp;
	afx_msg CString CTMDlg::ReadStringU(CFile& m_fileUnicodeFile);
	afx_msg void CTMDlg::WriteStringU(CFile& m_fileUnicodeFile, TCHAR *m_strUnicodeString);
	afx_msg CTMDlg::CString Crypt(TCHAR *m_strInput, size_t m_nInputLength, TCHAR *m_strKey, size_t m_nKeyLength);
		CString m_strKey;
		int m_nAddValuePerLine;
		CString m_strTestTitle;
		int m_nImageFlag[150];
		CString m_strImageName[150]; 
		int m_nNumberOfAnswers[150];
		int m_nMixArrayMaxLimit;
		int m_nMixArrayUpperLimit;
		int m_nMixArrayKeyNumber;
	afx_msg void CTMDlg::RandomMaker(int m_nMixArrayMaxLimit, int m_nMixArrayUpperLimit, int m_nMixArrayKeyNumber);
		int m_nMixArray[150];
		CString m_strQuestion[150];
		CString m_strAnswers[150][4];
		CString m_strCorrectAnswer[150];
		CString m_strExplanation[150];
		int m_nNumberOfQuestions;
	afx_msg void CTMDlg::ResetTest(void);
		int m_nCount;
		int m_nTrueCount;
		bool m_bEnableRadio;
		int m_nNumberCorrect;
		bool m_bTestCompleteFlag;
		int m_nScoreCount;
		CTime m_tStartTime;
	afx_msg void CTMDlg::PrepScreen(void);
		CString m_strStaticQuestionCounter;
		CString m_strRadioTextSelected[150];
	afx_msg void CTMDlg::EnableScreen(void);
	afx_msg void CTMDlg::OnMainSaveTheCurrentTest(void);
	afx_msg void CTMDlg::OnMainLoadAPreviousTest(void);
	afx_msg void CTMDlg::OnOptionsAlwaysOnTop(void);
	afx_msg void CTMDlg::OnUpdateOptionsAlwaysOnTop(CCmdUI *pCmdUI);
		int m_nAlwaysOnTopToggle;
	afx_msg void CTMDlg::OnOptionsProvideFeedback(void);
	afx_msg void CTMDlg::OnUpdateOptionsProvideFeedback(CCmdUI *pCmdUI);
		int m_nProvideFeedbackToggle;
	afx_msg void CTMDlg::OnOptionsRandomizeQuestionOrder(void);
	afx_msg void CTMDlg::OnUpdateOptionsRandomizeQuestionOrder(CCmdUI *pCmdUI);
		int m_nRandomizeQuestionOrderToggle;
	afx_msg void CTMDlg::OnOptionsShowClock(void);
	afx_msg void CTMDlg::OnUpdateOptionsShowClock(CCmdUI *pCmdUI);
		int m_nShowClockToggle;
	afx_msg void CTMDlg::OnTimer(UINT nIDEvent);
		CTimeSpan m_tElapsedTime;	
		CString m_strStaticClock;
	afx_msg void CTMDlg::OnFileExitTestMate(void);
	afx_msg void CTMDlg::OnHelp(void);
	afx_msg void CTMDlg::OnHelpAboutTestMate(void);
	afx_msg void CTMDlg::OnBnClickedReviewButton(void);
	afx_msg void CTMDlg::OnBnClickedShowScore(void);
	afx_msg void CTMDlg::OnBnClickedNextButton(void);
		int m_nRadioButtonSelected;
	afx_msg void CTMDlg::OnOK(void);
	afx_msg void CTMDlg::OnCancel(void);
DECLARE_MESSAGE_MAP()
afx_msg void OnHelpALetterToAllServiceMembers();
};