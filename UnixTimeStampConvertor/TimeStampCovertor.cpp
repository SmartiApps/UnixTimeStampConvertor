#include "StdAfx.h"
#include "TimeStampCovertor.h"
CTimeStampCovertor::CTimeStampCovertor(void)
{
}

CTimeStampCovertor::~CTimeStampCovertor(void)
{
}
//e.g. 1331812987 = Thu 15 Mar 2012 01:03:07 PM CET
CString CTimeStampCovertor::ConvertUnixToTimeStamp(LPCTSTR lpTime) {
	CString csTime;
	time_t t;
	struct tm *ptrTm;
	t = (time_t) atoi(lpTime);
	ptrTm=localtime(&t);
	csTime=asctime(ptrTm);
	return csTime;
}
int CTimeStampCovertor::ConvertUnixToTimeStamp(const CString &csFileContent,LPCTSTR lpStart,LPCTSTR lpEnd, CString &csConvertedContent) 
{
	int nPos=0;//For Last End value
	int nPosStart=0,nPosEnd=0;
	CString csUnixTimeStamp;
	csConvertedContent.Empty();
	while( (nPosStart=csFileContent.Find(lpStart,nPos))>-1 && (nPosEnd=csFileContent.Find(lpEnd,nPosStart+_tcslen(lpStart)))>-1)
	{
		if(csConvertedContent.IsEmpty())
		{
			csConvertedContent=csFileContent.Left(nPosEnd+_tcslen(lpEnd));
		}
		else
		{
			csConvertedContent+=csFileContent.Mid(nPos,nPosEnd+_tcslen(lpEnd)-nPos);//From Last end to current start
		}
		csUnixTimeStamp=csFileContent.Mid(nPosStart+_tcslen(lpStart),nPosEnd-(nPosStart+_tcslen(lpStart)));

		nPos=nPosEnd+_tcslen(lpEnd);
		if(csUnixTimeStamp.GetLength()>10)
		{
			csUnixTimeStamp=csUnixTimeStamp.Left(10);
		}

		csConvertedContent+=ConvertUnixToTimeStamp(csUnixTimeStamp);

	}
	if(nPos>-1)
		csConvertedContent+=csFileContent.Mid(nPos);
	else if(nPos==0)
		csConvertedContent=csFileContent;


	return 1;
}
