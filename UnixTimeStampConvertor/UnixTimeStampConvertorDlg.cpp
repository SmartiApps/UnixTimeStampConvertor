
// UnixTimeStampConvertorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UnixTimeStampConvertor.h"
#include "UnixTimeStampConvertorDlg.h"
#include "TimeStampCovertor.h"
#include "Utils.h"
#include "OptionsDlg.h"
#include "hyperlink.h"
#pragma comment(lib,"Version.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	virtual BOOL OnInitDialog();
	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CHyperLink m_stwebLink;
	CHyperLink m_stEmail;
	CStatic m_stVersion;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_WEB, m_stwebLink);
	DDX_Control(pDX, IDC_ST_EMAIL, m_stEmail);
	DDX_Control(pDX, IDC_ST_VER, m_stVersion);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUnixTimeStampConvertorDlg dialog

BOOL GetAppVersion( char *LibName, WORD *MajorVersion, WORD *MinorVersion, WORD *BuildNumber, WORD *RevisionNumber )
{
	DWORD dwHandle, dwLen;
	UINT BufLen;
	LPTSTR lpData;
	VS_FIXEDFILEINFO *pFileInfo;
	dwLen = GetFileVersionInfoSize( LibName, &dwHandle );
	if (!dwLen) 
		return FALSE;

	lpData = (LPTSTR) malloc (dwLen);
	if (!lpData) 
		return FALSE;

	if( !GetFileVersionInfo( LibName, dwHandle, dwLen, lpData ) )
	{
		free (lpData);
		return FALSE;
	}
	if( VerQueryValue( lpData, "\\", (LPVOID *) &pFileInfo, (PUINT)&BufLen ) ) 
	{
		*MajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
		*MinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
		*BuildNumber = HIWORD(pFileInfo->dwFileVersionLS);
		*RevisionNumber = LOWORD(pFileInfo->dwFileVersionLS);
		free (lpData);
		return TRUE;
	}
	free (lpData);
	return FALSE;
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csVersion;

	WORD MajorVersion        =0; 
	WORD MinorVersion        =0; 
	WORD BuildNumber        =0; 
	WORD RevisionNumber        =0;

	TCHAR fileName[4096];
	GetModuleFileName(NULL,fileName,4096);
	//theApp.m_pszExeName is no good

	GetAppVersion(fileName,
		&MajorVersion,    
		&MinorVersion,    
		&BuildNumber,    
		&RevisionNumber);

	csVersion.Format (_T("%hu.%hu"),MajorVersion,MinorVersion);

	m_stVersion.SetWindowText(csVersion);
	m_stwebLink.SetURL("http://www.smartpricedeal.com/products/");
	return TRUE;
}




CUnixTimeStampConvertorDlg::CUnixTimeStampConvertorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUnixTimeStampConvertorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SMART);
}

void CUnixTimeStampConvertorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILES, m_lstFiles);
	DDX_Control(pDX, IDC_EDIT_UNIX_TIMESTAMP, m_edUnixTimeStamp);
	DDX_Control(pDX, IDC_EDIT_TIMESTAMP, m_edTime);
}

BEGIN_MESSAGE_MAP(CUnixTimeStampConvertorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDOK, &CUnixTimeStampConvertorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CONVERT, &CUnixTimeStampConvertorDlg::OnBnClickedBtnConvert)
	ON_COMMAND(ID_FILE_EXIT, &CUnixTimeStampConvertorDlg::OnFileExit)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CUnixTimeStampConvertorDlg::OnToolsOptions)
	//ON_BN_CLICKED(IDCANCEL, &CUnixTimeStampConvertorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CONVERTFILES, &CUnixTimeStampConvertorDlg::OnBnClickedBtnConvertfiles)
	ON_COMMAND(ID_HELP_ABOUT, &CUnixTimeStampConvertorDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CUnixTimeStampConvertorDlg message handlers

BOOL CUnixTimeStampConvertorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUnixTimeStampConvertorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUnixTimeStampConvertorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUnixTimeStampConvertorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*

void CUnixTimeStampConvertorDlg::OnBnClickedOk()
{
CString csUnixTime="1408606726";//175";
CString csTime;
CTimeStampCovertor obj;
csTime=obj.ConvertUnixToTimeStamp(csUnixTime);
AfxMessageBox(csTime);
// TODO: Add your control notification handler code here
//OnOK();
}

*/
void CUnixTimeStampConvertorDlg::OnBnClickedBtnConvert()
{
	m_edTime.SetWindowText("");
	CTimeStampCovertor obj;
	CString csUnixTime,csConvertedTime;
	m_edUnixTimeStamp.GetWindowText(csUnixTime);
	if(csUnixTime.GetLength()>10)
		csUnixTime=csUnixTime.Left(10);

	csConvertedTime=obj.ConvertUnixToTimeStamp(csUnixTime);
	m_edTime.SetWindowText(csConvertedTime);

}

void CUnixTimeStampConvertorDlg::OnFileExit()
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CUnixTimeStampConvertorDlg::OnToolsOptions()
{
	COptionsDlg dlg;
	dlg.DoModal();
}
/*
void CUnixTimeStampConvertorDlg::OnBnClickedCancel()
{
// TODO: Add your control notification handler code here
OnCancel();
// AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
*/
void CUnixTimeStampConvertorDlg::OnBnClickedBtnConvertfiles()
{
	int nCount=m_lstFiles.GetCount();
	CString csFilePath,csFileContent;
	CString csConverDirectoryPath,csPostCmd;
	CString csStart,csEnd;

	csConverDirectoryPath=CUtils::GetConvertedFilesPath();
	csStart=CUtils::GetIniSettingsString("Settings","Stringstart");
	csEnd=CUtils::GetIniSettingsString("Settings","StringEnd");
	csPostCmd=CUtils::GetIniSettingsString("Settings","PostCommand");
	if(csStart.IsEmpty()||csEnd.IsEmpty())
	{
		AfxMessageBox("Please check the String Settings");
		return;
	}

	for(int i=0;i<nCount;++i)
	{		
		m_lstFiles.GetText(i,csFilePath);
		if(	CUtils::ReadFromFile(csFilePath,csFileContent)>0)
		{
			CTimeStampCovertor obj;
			CString csTime;
			obj.ConvertUnixToTimeStamp(csFileContent,csStart,csEnd,csTime);
			CUtils::WriteToFileEx(csConverDirectoryPath,csFilePath,csTime);
			if(!csPostCmd.IsEmpty())
			{
				CUtils::OpenFileInEditor(csPostCmd,csFilePath);
			}
		}
	}
	if(csPostCmd.IsEmpty())
	{
		AfxMessageBox("Successsfully Competed");
	}
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CUnixTimeStampConvertorDlg::OnHelpAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
