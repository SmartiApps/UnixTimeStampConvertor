#include "stdafx.h"
#include "Utils.h"

//For GUID COM lib
#pragma comment (lib, "Rpcrt4.lib")
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

CString  CUtils::m_csAppDataPath="";
CString  CUtils::m_csGetConvertedFilesPath="";
CString  CUtils::m_csIniPath="";
#define APPLICATIONNAME "SmartUnixTimeStampConvertor1.0"
#define CONVERTERPATH "ConvertedFiles"
#define SETTINGSPATH "settings"
CUtils::CUtils(void)
{
}

CUtils::~CUtils(void)
{
}


//To Generate GUID
CString CUtils::GetUniqueGUID( ) 
{ 
	HRESULT hr = NULL; 
	CString sUUID(_T("")); 
	UUID *pUUID = NULL; 
	BOOL bAllocated = FALSE; 
	unsigned char *sTemp = NULL; 

	if (pUUID == NULL) 
	{ 
		pUUID = new UUID; 
		bAllocated = TRUE; 
	} 

	if (pUUID != NULL) 
	{ 
		hr = UuidCreate( pUUID ); 
		if (hr == RPC_S_OK) 
		{ 
			hr = UuidToString(pUUID, &sTemp); 
			if (hr == RPC_S_OK) 
			{ 
				sUUID = sTemp; 
				sUUID.MakeUpper(); 
				RpcStringFree(&sTemp); 
			} 
		} 
		if (bAllocated) 
		{ 
			delete pUUID; 
			pUUID = NULL; 
		} 
	} 
	return sUUID; 
} 

int CUtils::ReadFromFile(LPCTSTR lpcFileName, CString &cContents)
{
	if( !lpcFileName || lpcFileName[0]=='\0' )
	{
		return -1;
	}	
	CFile cf;
	CFileStatus status;
	TCHAR *szText = NULL;
	CFileException cfe;

	try
	{
		if(!cf.Open(lpcFileName, CFile::modeRead|CFile::shareDenyWrite, &cfe))
		{
			//WriteLog("GetContentsFromFile - Open file error");
			return -1;
		}

		cf.GetStatus(status);
		szText = new TCHAR[status.m_size + 1];
		cf.Read(szText,status.m_size);
		szText[status.m_size]=0;
		cContents = szText;

		if(szText)
		{
			delete[] szText;
			szText = NULL;
		}	
		cf.Close();

	}
	catch(CFileException *ce)
	{
		ce->Delete();
		cf.Close();		
		return -1;
	}


	return 1;
}

BOOL CUtils::DoesFileExist(LPCTSTR lpcFileName )
{
	if( !lpcFileName || lpcFileName[0]=='\0' )
	{
		return FALSE;
	}

	CFileStatus status;
	BOOL bRet = FALSE;

	bRet = CFile::GetStatus (lpcFileName, status );
	return bRet;
}

int CUtils::WriteToFile(LPCTSTR lpcFileName, LPCTSTR lpcText)
{
	if( !lpcFileName || lpcFileName[0]=='\0' )
	{
		return -1;
	}
	if(!lpcText || lpcText[0]=='\0') return -1;


	CFile cf;
	CFileException cfe;

	try
	{
		if(!cf.Open(lpcFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite, &cfe))
		{
			return 0;
		}

		cf.Write(lpcText, lstrlen(lpcText) );
		cf.Close();
	}
	catch(CFileException *ce)
	{
		ce->Delete();
		cf.Close();

		return -1;
	}

	return 1;
}

int CUtils::AppendToFile(LPCTSTR lpFileName, LPCTSTR lpData)
{
	CString csFileName = lpFileName;
	CString csData = lpData;
	if(csFileName.IsEmpty() || csData.IsEmpty())
	{
		return -1;
	}


	CStdioFile cf;
	if(	cf.Open(lpFileName,CFile::modeCreate| CFile::modeWrite|CFile::modeNoTruncate)<=0)
	{
		return -1;
	}
	cf.SeekToEnd();
	cf.WriteString(csData+ "\n");

	cf.Close();
	return 1;
}


void CUtils::WriteToFileEx(CString & csFileName , CString & csHtmlContent ) 
{ 

	CFileStatus cf; 
	if(CFile::GetStatus(csFileName,cf)) // File Exist 
	{ 
		CString csExt ; 
		CString csGUID=GetUniqueGUID(); 
		csGUID = "_"+csGUID; 
		int nPos = csFileName.ReverseFind('.'); 
		if(nPos > -1 ) 
		{ 
			csExt = csFileName.Mid(nPos); 
			csFileName = csFileName.Left(nPos); 
			csFileName = csFileName+csGUID+csExt; 
		} 
	} 
	WriteToFile(csFileName,csHtmlContent);
}
void CUtils::WriteToFileEx(LPCTSTR lpcFolderPath, CString & csFileName , CString & csHtmlContent ) 
{ 

	CFileStatus cf; 
	if(CFile::GetStatus(csFileName,cf)) // File Exist 
	{ 
		CString csExt ; 
		CString csGUID=GetUniqueGUID(); 
		csGUID = "_"+csGUID; 
		int nPos = csFileName.ReverseFind('.'); 
		if(nPos > -1 ) 
		{ 
			csExt = csFileName.Mid(nPos); 
			csFileName = lpcFolderPath+csGUID+csExt; 
		} 
	} 
	WriteToFile(csFileName,csHtmlContent);
}

CString CUtils::GetExePath ()
{ 
	TCHAR szPath[_MAX_PATH];
	szPath[0] = '\0';

	GetModuleFileName( NULL, szPath, sizeof(szPath) );

	CString csPath(szPath);

	int posn = csPath.ReverseFind('\\');
	if ( posn != -1)
	{
		csPath = csPath.Left(posn+1);
	}
	else
	{
		csPath = ""; 
	}

	return csPath;

}


CString CUtils::GetDLLPath()
{
	TCHAR szPath[_MAX_PATH];
	szPath[0] = '\0';
	GetModuleFileName((HINSTANCE)&__ImageBase, szPath, sizeof(szPath) );
	CString csDllPath(szPath);
	return csDllPath;
}
CString CUtils::GetAppDataPath()
{
	if(!m_csAppDataPath.IsEmpty())
		return m_csAppDataPath;

	CString csPath;
	TCHAR szPath[MAX_PATH];
	int nSize=0;
	SHGetFolderPath(NULL,CSIDL_LOCAL_APPDATA,NULL,nSize,szPath);
	//To do later
	csPath=szPath;
	csPath=csPath+"\\"+APPLICATIONNAME+"\\";
	m_csAppDataPath =csPath;
	if(FALSE==DoesFileExist(m_csAppDataPath))
		CreateDirectory(m_csAppDataPath,NULL);
	return m_csAppDataPath;
}

CString CUtils::GetSettingsIni()
{
	if(!m_csIniPath.IsEmpty())
		return m_csIniPath;
	m_csIniPath=GetAppDataPath()+SETTINGSPATH+"\\";
	if(FALSE==DoesFileExist(m_csIniPath))
		CreateDirectory(m_csIniPath,NULL);

	m_csIniPath=m_csIniPath+"settings.ini";
	return m_csIniPath;
}


int CUtils::ReadContentsFromFile(LPCTSTR lpcFileName, CString &cContents)
{
	if( !lpcFileName || lpcFileName[0]=='\0' )
	{
		return -1;
	}

	HANDLE hfile;
	try
	{
		hfile=CreateFile(lpcFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
		if(INVALID_HANDLE_VALUE == hfile)
			return -1;

		DWORD dwSize = GetFileSize(hfile, NULL);
		TCHAR *szText = new TCHAR[dwSize+ 1];
		memset(szText,0,dwSize+ 1);
		DWORD dwBytes = 0;
		ReadFile(hfile, szText, dwSize+ 1, &dwBytes, NULL);			
		cContents = szText;

		if(szText)
		{
			delete[] szText;
			szText = NULL;

		}	
		CloseHandle(hfile);
	}
	catch(...)
	{
		return -1;
	}

	return 1;
}

CString CUtils::ReadReturnValueOfCmdFile(CString csExeName, CString csArguments)
{
	CString csExecute;
	csExecute=csExeName + " " + csArguments;

	SECURITY_ATTRIBUTES secattr;
	ZeroMemory(&secattr,sizeof(secattr));
	secattr.nLength = sizeof(secattr);
	secattr.bInheritHandle = TRUE;

	HANDLE rPipe, wPipe;

	//Create pipes to write and read data

	CreatePipe(&rPipe,&wPipe,&secattr,0);
	//

	STARTUPINFO sInfo;
	ZeroMemory(&sInfo,sizeof(sInfo));
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&pInfo,sizeof(pInfo));
	sInfo.cb=sizeof(sInfo);
	sInfo.dwFlags=STARTF_USESTDHANDLES;
	sInfo.hStdInput=NULL;
	sInfo.hStdOutput=wPipe;
	sInfo.hStdError=wPipe;
	char command[1024]; strcpy(command, 
		csExecute.GetBuffer(csExecute.GetLength()));

	//Create the process here.

	CreateProcess(0, command,0,0,TRUE,
		NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW,0,0,&sInfo,&pInfo);
	CloseHandle(wPipe);

	//now read the output pipe here.

	char buf[100];
	DWORD reDword;
	CString m_csOutput,csTemp;
	BOOL res;
	do
	{
		res=::ReadFile(rPipe,buf,100,&reDword,0);
		csTemp=buf;
		m_csOutput+=csTemp.Left(reDword);
	}while(res);
	return m_csOutput;
}
int CUtils::OpenFileInEditor(CString csExepathAndArg, CString csFilePath)
{
	CString csExecute;
	csExecute=csExepathAndArg + " " + csFilePath;
/*
	SECURITY_ATTRIBUTES secattr;
	ZeroMemory(&secattr,sizeof(secattr));
	secattr.nLength = sizeof(secattr);
	secattr.bInheritHandle = TRUE;

	HANDLE rPipe, wPipe;
*/
	//Create pipes to write and read data

	//CreatePipe(&rPipe,&wPipe,&secattr,0);
	//

	STARTUPINFO sInfo;
	ZeroMemory(&sInfo,sizeof(sInfo));
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&pInfo,sizeof(pInfo));
	sInfo.cb=sizeof(sInfo);
	sInfo.dwFlags=STARTF_USESTDHANDLES;
	sInfo.hStdInput=NULL;
	sInfo.hStdOutput=NULL;//wPipe;
	sInfo.hStdError=NULL;//wPipe;
	char command[1024]; strcpy(command, 
		csExecute.GetBuffer(csExecute.GetLength()));

	//Create the process here.

	CreateProcess(0, command,0,0,TRUE,
		NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW,0,0,&sInfo,&pInfo);
	//CloseHandle(wPipe);

	//now read the output pipe here.

	//char buf[100];
	//DWORD reDword;
	//CString m_csOutput,csTemp;
	//BOOL res;
	//do
	//{
	//	res=::ReadFile(rPipe,buf,100,&reDword,0);
	//	csTemp=buf;
	//	m_csOutput+=csTemp.Left(reDword);
	//}while(res);
	//return m_csOutput;
	return 1;
}

CString CUtils::GetStringFromIni(const char* const szPath, const char* const szAppName,const char* const szKey)
{
	CString csPath;
	GetPrivateProfileString(szAppName,szKey,"",csPath.GetBuffer(1024),1024,szPath);
	csPath.ReleaseBuffer();
	return csPath;
}
CString CUtils::GetIniSettingsString(const char* const szAppName,const char* const szKey)
{
	CString csValue;
	GetPrivateProfileString(szAppName,szKey,"",csValue.GetBuffer(1024),1024,GetSettingsIni());
	csValue.ReleaseBuffer();
	return csValue;
}
int CUtils::GetIniSettingsInt(const char* const szAppName,const char* const szKey)
{
	int nRet=-1;
	nRet=GetPrivateProfileInt(szAppName,szKey,-1,GetSettingsIni());
	return nRet;
}	
int CUtils::WriteIniSettingsString(const char* const szAppName,const char* const szKey,CString csValue)
{
	int nRet=0;
	nRet=	WritePrivateProfileString(szAppName,szKey,csValue,GetSettingsIni());
	return nRet;
}



void CUtils::SetClipboardText(const CString &csText) 
{
	//put your text in source
	if(OpenClipboard(NULL))
	{
		HGLOBAL hGlobal;
		char * buffer;
		EmptyClipboard();
		hGlobal = GlobalAlloc(GMEM_DDESHARE, csText.GetLength()+1);
		buffer = (char*)GlobalLock(hGlobal);
		strcpy(buffer, LPCSTR(csText));
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_TEXT,hGlobal);
		CloseClipboard();
	}
} 
void CUtils::Paste() 
{
	// Create a generic keyboard event structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
CString CUtils::GetConvertedFilesPath()
{
	if(!m_csGetConvertedFilesPath.IsEmpty())
		return m_csGetConvertedFilesPath;
	m_csGetConvertedFilesPath=GetAppDataPath()+CONVERTERPATH+"\\";
	if(FALSE==DoesFileExist(m_csGetConvertedFilesPath))
		CreateDirectory(m_csGetConvertedFilesPath,NULL);

	return m_csGetConvertedFilesPath;
}


