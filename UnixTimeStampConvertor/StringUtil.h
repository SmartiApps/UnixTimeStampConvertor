#pragma once
#include <string>
#include <vector>

using namespace std;
class CStringUtil
{
public:
	CStringUtil(void);
	~CStringUtil(void);
		//string
	
	static BOOL ConvertHtmlSplChars(CString& csHtml);
	static CStringA UTF16toUTF8(const CStringW& utf16);
	static CStringW UTF8toUTF16(const CStringA& utf8);
	static BOOL UTF8ToHtml(BYTE *utf8, DWORD dwSize, CHAR *ptr );
	static bool WildcardCompareNoCase	(LPCTSTR strWild, LPCTSTR strText);
	static bool WildcardCompare			(LPCTSTR strWild, LPCTSTR strText);

	//util
	static CString GetContentBetweenStrings(const CString& csInput, LPCTSTR lpStart, LPCTSTR lpEnd);
	static int GetAllContentBetweenStrings(const CString& csInput, LPCTSTR lpStart, LPCTSTR lpEnd,CStringArray &csaOutput);
	static void ReplaceInvaildChractersWithSpace(CString& csInput);
	static int SplitString(const CString& csInput,   const CString& csDelimiter, CStringArray& csaResults);
	static int SplitString(const string& input, const string& delimiter, vector<string>& results,   bool includeEmpties = true);

	static void RemoveTags(CString &csHtml,LPCTSTR lpStartTag, LPCTSTR lpEndTag );
	static void RemoveHTMLComments(CString &csHtml);
	static int CountCharacters(LPCTSTR lpcTxt, char chrToCount);
	static BOOL IsNumber(LPCTSTR lpcTxt);
	static int CountDigits(LPCTSTR lpcTxt);
	static BOOL DoesContainDigit(LPCTSTR lpcTxt);
	static BOOL DoesContainAlphabet(LPCTSTR lpcTxt);
	static int LastFindOf(const CString &csContent, LPCTSTR lpcFind);
	static void GetValidFileName(CString &csFileName);
	static void GetValidFilePath(CString &csFilePath);

};
