
// UnixTimeStampConvertorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "DropListBox.h"

// CUnixTimeStampConvertorDlg dialog
class CUnixTimeStampConvertorDlg : public CDialog
{
// Construction
public:
	CUnixTimeStampConvertorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UNIXTIMESTAMPCONVERTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	CDropListBox m_lstFiles;
	afx_msg void OnBnClickedBtnConvert();
	afx_msg void OnFileExit();
	afx_msg void OnToolsOptions();
	//afx_msg void OnBnClickedCancel();
	CEdit m_edUnixTimeStamp;
	CEdit m_edTime;
	afx_msg void OnBnClickedBtnConvertfiles();
	afx_msg void OnHelpAbout();
};
