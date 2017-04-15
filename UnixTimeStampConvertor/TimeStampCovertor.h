#pragma once

class CTimeStampCovertor
{
public:
	CTimeStampCovertor(void);
	~CTimeStampCovertor(void);
	CString ConvertUnixToTimeStamp(LPCTSTR lpTime);
	
	int ConvertUnixToTimeStamp(const CString &csFileContent,LPCTSTR lpStart,LPCTSTR lpEnd, CString &csConvertedContent);
};
