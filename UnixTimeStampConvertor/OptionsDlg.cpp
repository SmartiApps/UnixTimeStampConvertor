// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UnixTimeStampConvertor.h"
#include "OptionsDlg.h"
#include "Utils.h"


// COptionsDlg dialog

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STR_START, m_edStart);
	DDX_Control(pDX, IDC_EDIT_STR_END, m_edEnd);
	DDX_Control(pDX, IDC_EDIT_CMD, m_edCmd);
	DDX_Control(pDX, IDC_EDIT_PATH, m_edPath);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_BN_CLICKED(ID_SAVE, &COptionsDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDCANCEL, &COptionsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	

	m_edPath.SetWindowText(CUtils::GetConvertedFilesPath());
	m_edStart.SetWindowText(CUtils::GetIniSettingsString("Settings","Stringstart"));
	m_edEnd.SetWindowText(CUtils::GetIniSettingsString("Settings","StringEnd"));
	m_edCmd.SetWindowText(CUtils::GetIniSettingsString("Settings","PostCommand"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// COptionsDlg message handlers

void COptionsDlg::OnBnClickedSave()
{
	CString csParseStrStart,csParseStrEnd,csPostBuildCmd;

	m_edStart.GetWindowText(csParseStrStart);
	m_edEnd.GetWindowText(csParseStrEnd);
	m_edCmd.GetWindowText(csPostBuildCmd);
	CUtils::WriteIniSettingsString("Settings","Stringstart",csParseStrStart);
	CUtils::WriteIniSettingsString("Settings","StringEnd",csParseStrEnd);
	CUtils::WriteIniSettingsString("Settings","PostCommand",csPostBuildCmd);
	OnCancel();
}

void COptionsDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}


