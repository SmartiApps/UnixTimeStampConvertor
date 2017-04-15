#pragma once

class CUtils
{
public:
	CUtils(void);
	~CUtils(void);

	//GUID
	static CString GetUniqueGUID( ) ;

	//File Operation Functions
	static int ReadFromFile(LPCTSTR lpcFileName, CString &cContents);
	static BOOL DoesFileExist(LPCTSTR lpcFileName );
	static int WriteToFile(LPCTSTR lpcFileName, LPCTSTR lpcText);
	static int AppendToFile(LPCTSTR lpFileName, LPCTSTR lpData);
	static void WriteToFileEx(CString & csFileName , CString & csHtmlContent ) ;
	static int ReadContentsFromFile(LPCTSTR lpcFileName, CString &cContents);
	static CString ReadReturnValueOfCmdFile(CString csExeName, CString csArguments);
	static void WriteToFileEx(LPCTSTR lpcFolderPath, CString & csFileName , CString & csHtmlContent ) ;

	//Folder Path
	static CString GetDLLPath();
	static CString GetExePath ();
	static CString GetAppDataPath();
	static CString GetConvertedFilesPath();
	static CString GetSettingsIni();

	static CString  m_csAppDataPath;
	static CString  m_csGetConvertedFilesPath;
	static CString  m_csIniPath;
	static CString GetStringFromIni(const char* const szPath, const char* const szAppName,const char* const szKey);
	
	static CString GetIniSettingsString(const char* const szAppName,const char* const szKey);
	static int GetIniSettingsInt(const char* const szAppName,const char* const szKey);
	static int WriteIniSettingsString(const char* const szAppName,const char* const szKey,CString csValue);

	static void SetClipboardText(const CString &csText) ;
	static void Paste();
	static int OpenFileInEditor(CString csExepathAndArg, CString csFilePath);

};
