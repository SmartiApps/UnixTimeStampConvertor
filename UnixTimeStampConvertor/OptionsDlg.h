#pragma once
#include "afxwin.h"


// COptionsDlg dialog

class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();
	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DLG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();

	CEdit m_edStart;
	CEdit m_edEnd;
	CEdit m_edCmd;
	CEdit m_edConvertPath;
	CEdit m_edPath;
};
