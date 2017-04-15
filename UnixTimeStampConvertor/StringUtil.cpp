#include "stdafx.h"
#include "StringUtil.h"

CStringUtil::CStringUtil(void)
{
}

CStringUtil::~CStringUtil(void)
{
}

BOOL CStringUtil::ConvertHtmlSplChars(CString& csHtml)
{
	LPTSTR    lptstr;
	lptstr=csHtml.GetBuffer(csHtml.GetLength()+1);
	if (lptstr != NULL) 
	{

		char *ptr1=lptstr;
		int iSize = lstrlen(lptstr);
		char * tmp = (char*)malloc( iSize * 2 ); //_alloca
		UTF8ToHtml((BYTE*)ptr1, iSize, tmp );				
		csHtml = tmp;
		free(tmp);

	}

	return TRUE;
}

BOOL CStringUtil::UTF8ToHtml(BYTE *utf8, DWORD dwSize, CHAR *ptr )
{
	int code;
	BYTE *end = utf8 + dwSize;
	while( utf8 < end )
	{
		code = 0;
		if( (*utf8 & 0xF0) == 0xF0  )
		{
			code = (((*utf8)&0x0F) << 18) | (((*(utf8+1))
				& 0x7F)<<12) | (((*(utf8+2)) & 0x7F)<<6)
				| ((*(utf8+3)) & 0x7F );
			utf8+=3;
		}
		else
		{
			if( (*utf8 & 0xE0) == 0xE0 )
			{
				code = (((*utf8)&0x1F) << 12) | (((*(utf8+1))
					& 0x7F)<<6 ) | ((*(utf8+2)) & 0x7F );
				utf8+=2;
			}
			else
			{
				if( (*utf8 & 0xC0) == 0xC0 )
				{
					code = (((*utf8)&0x3F) << 6) | ((*(utf8+1)) & 0x7F) ;
					utf8+=1;
				}
			}
		}


		if( code == 0 )
		{
			*ptr = *utf8;
		}
		else
		{
			char s[10];
			switch(code)
			{
				/*case 160:
				strcpy(s, "& ");
				break;
				case 34:
				strcpy(s, "&");
				break;
				case 36:
				strcpy( s, "&&");
				break;
				case 60:
				strcpy( s, "&<");
				break;
				case 62:
				strcpy( s, "&>");
				break;*/
			default:
				sprintf( s, "&#%d;", code );
				break;
			}
			strcpy( ptr, s );
			ptr += strlen(s)-1;
		}
		utf8++;
		ptr++;
	}
	*ptr = 0;
	return TRUE;
}

CStringW CStringUtil::UTF8toUTF16(const CStringA& utf8)
{
	CStringW utf16;
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	if (len>1)
	{ 
		wchar_t *ptr = utf16.GetBuffer(len-1);
		if (ptr) MultiByteToWideChar(CP_UTF8, 0, utf8, -1, ptr, len);
		utf16.ReleaseBuffer();
	}
	return utf16;
}
CStringA CStringUtil::UTF16toUTF8(const CStringW& utf16)
{
	CStringA utf8;
	int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, 0, 0);
	if (len>1)
	{ 
		char *ptr = utf8.GetBuffer(len-1);
		if (ptr) WideCharToMultiByte(CP_UTF8, 0, utf16, -1, ptr, len, 0, 0);
		utf8.ReleaseBuffer();
	}
	return utf8;
}


bool CStringUtil::WildcardCompareNoCase (LPCTSTR strWild, LPCTSTR strText)
{
	int cp = 0, mp = 0;
	int idxWild = 0, idxString = 0;
	int nStrLen = _tcslen (strText);
	int nWildLen = _tcslen (strWild);

	while (idxString < nStrLen)
	{
		if (idxWild >= nWildLen)
			break;
		if (strWild [idxWild] == _T ('*'))
			break;

		if ((toupper (strWild [idxWild]) != toupper (strText [idxString]) && (strWild [idxWild] != _T ('?'))))
			return false;

		++ idxWild;
		++ idxString;
	}

	while (idxString < nStrLen) 
	{
		if (idxWild >= nWildLen)
			break;

		if (strWild [idxWild] == _T ('*')) 
		{
			++ idxWild;
			if (idxWild >= nWildLen)
				return true;

			mp = idxWild;
			cp = idxString + 1;
		} 
		else if ((toupper (strWild [idxWild]) == toupper (strText [idxString])) || (strWild [idxWild] == _T ('?'))) 
		{
			++ idxWild;
			++ idxString;
		}
		else 
		{
			idxWild = mp;
			idxString = cp ++;
		}
	}

	while (idxWild < nWildLen)
	{
		if (strWild [idxWild] != _T ('*'))
			break;
		++ idxWild;
	}

	if (idxWild < nWildLen)
		return false;
	else
		return true;
}

bool CStringUtil::WildcardCompare (LPCTSTR strWild, LPCTSTR strText)
{
	int cp = 0, mp = 0;
	int idxWild = 0, idxString = 0;
	int nStrLen = _tcslen (strText);
	int nWildLen = _tcslen (strWild);

	while (idxString < nStrLen)
	{
		if (idxWild >= nWildLen)
			break;
		if (strWild [idxWild] == _T ('*'))
			break;

		if ((strWild [idxWild] != strText [idxString] && (strWild [idxWild] != _T ('?'))))
			return false;

		++ idxWild;
		++ idxString;
	}

	while (idxString < nStrLen) 
	{
		if (idxWild >= nWildLen)
			break;

		if (strWild [idxWild] == _T ('*')) 
		{
			++ idxWild;
			if (idxWild >= nWildLen)
				return true;

			mp = idxWild;
			cp = idxString + 1;
		} 
		else if ((strWild [idxWild] == strText [idxString]) || (strWild [idxWild] == _T ('?'))) 
		{
			++ idxWild;
			++ idxString;
		}
		else 
		{
			idxWild = mp;
			idxString = cp ++;
		}
	}

	while (idxWild < nWildLen)
	{
		if (strWild [idxWild] != _T ('*'))
			break;
		++ idxWild;
	}

	if (idxWild < nWildLen)
		return false;
	else
		return true;
}
CString CStringUtil::GetContentBetweenStrings(const CString& csInput, LPCTSTR lpStart, LPCTSTR lpEnd)
{
	int nPos=-1;
	CString csOutPut;
	if( (nPos=csInput.Find(lpStart)) >-1)
	{
		csOutPut=csInput.Mid(nPos+_tcslen(lpStart));
		if( (nPos=csOutPut.Find(lpEnd)) >-1)
		{
			csOutPut=csInput.Left(nPos);
		}
		else
			csOutPut.Empty();
	}
	return csOutPut;
}

int CStringUtil::GetAllContentBetweenStrings(const CString& csInput, LPCTSTR lpStart, LPCTSTR lpEnd, CStringArray &csaOutPut)
{
	int nPosStart=0;
	int nPosEnd=0;
	int nCount=0;
	csaOutPut.RemoveAll();
	//CString csOutPut;
	while( (nPosStart=csInput.Find(lpStart,nPosStart)) >-1)
	{
		//csOutPut=csInput.Mid(nPosStart+_tcslen(lpStart));
		if( (nPosEnd=csInput.Find(lpEnd,nPosStart+_tcslen(lpStart))) >-1)
		{
			csaOutPut.Add(csInput.Mid(nPosStart+_tcslen(lpStart),nPosEnd-(nPosStart+_tcslen(lpStart))));
			nCount++;
		}
		else
			break;
		nPosStart=nPosEnd+_tcslen(lpEnd);
	}
	return nCount;
}

void CStringUtil::ReplaceInvaildChractersWithSpace(CString& csInput)
{
	int nLen=csInput.GetLength();
	for(int nIndx=0;nIndx<nLen;nIndx++)
	{
		char chr=csInput.GetAt(nIndx);
		if(chr<0)
			csInput.Replace(chr,' ');

	}

}
//------------------------
// SplitString in MFC
//------------------------

int CStringUtil::SplitString(const CString& input, const CString& delimiter, CStringArray& results)
{	
	int iPos = 0;
	int newPos = -1;
	int sizeS2 = delimiter.GetLength();
	int isize = input.GetLength();
	results.RemoveAll();

	CArray<INT, int> positions;

	newPos = input.Find (delimiter, 0);

	if( newPos < 0 ) 
	{ 
		results.Add(input);
		return 0; 
	}
	else if(newPos==0)
	{
		int nPos=1;
		while(newPos==0 && input.GetLength()>0)
		{
			newPos = input.Find (delimiter, nPos);
			if(nPos==1 && newPos==-1 && input.GetLength()>1)
			{
				results.Add(input.Mid(1));
			}
			nPos++;
		}
	}


	int numFound = 0;

	while( newPos > iPos )
	{
		numFound++;
		positions.Add(newPos);
		iPos = newPos;
		newPos = input.Find (delimiter, iPos+sizeS2+1);
	}
	int nDelimitterPos=-1;
	for( int i=0; i < positions.GetSize(); i++ )
	{
		nDelimitterPos=positions[i] ;
		CString s;
		if( i == 0 )
			s = input.Mid( i,nDelimitterPos );
		else
		{
			int offset = positions[i-1] + sizeS2;
			if( offset < isize )
			{
				if( i == positions.GetSize() )
					s = input.Mid(offset);
				else if( i > 0 )
					s = input.Mid( positions[i-1] + sizeS2, 
					positions[i] - positions[i-1] - sizeS2 );
			}
		}
		if( s.GetLength() > 0 )
			results.Add(s);
	}
	if(input.GetLength()>nDelimitterPos)
	{
		results.Add(input.Mid(nDelimitterPos+delimiter.GetLength()));
	}
	return numFound;
}
int CStringUtil::SplitString(const string& input, 
							 const string& delimiter, vector<string>& results, 
							 bool includeEmpties)
{
	int iPos = 0;
	int newPos = -1;
	int sizeS2 = (int)delimiter.size();
	int isize = (int)input.size();

	if( 
		( isize == 0 )
		||
		( sizeS2 == 0 )
		)
	{
		return 0;
	}

	vector<int> positions;

	newPos = input.find (delimiter, 0);

	if( newPos < 0 )
	{ 
		return 0; 
	}

	int numFound = 0;

	while( newPos >= iPos )
	{
		numFound++;
		positions.push_back(newPos);
		iPos = newPos;
		newPos = input.find (delimiter, iPos+sizeS2);
	}

	if( numFound == 0 )
	{
		return 0;
	}

	for( int i=0; i <= (int)positions.size(); ++i )
	{
		string s("");
		if( i == 0 ) 
		{ 
			s = input.substr( i, positions[i] ); 
		}
		int offset = positions[i-1] + sizeS2;
		if( offset < isize )
		{
			if( i == positions.size() )
			{
				s = input.substr(offset);
			}
			else if( i > 0 )
			{
				s = input.substr( positions[i-1] + sizeS2, 
					positions[i] - positions[i-1] - sizeS2 );
			}
		}
		if( includeEmpties || ( s.size() > 0 ) )
		{
			results.push_back(s);
		}
	}
	return numFound;
}


void CStringUtil::RemoveTags(CString &csHtml,LPCTSTR lpStartTag, LPCTSTR lpEndTag )
{
	if(csHtml.IsEmpty())
		return;
   RemoveHTMLComments(csHtml);
    int nPosStart = -1;
	int nPosEnd = -1;

	while( (nPosStart=csHtml.Find(lpStartTag))>-1 && (nPosEnd=csHtml.Find(lpEndTag))>-1)
	{

		csHtml=csHtml.Left(nPosStart)+csHtml.Mid(nPosEnd+_tcslen(lpEndTag));
	}  

}
//<!--Footer Start -->

void CStringUtil::RemoveHTMLComments(CString &csHtml)
{
	if(csHtml.IsEmpty())
		return;
   
    int nPosStart = -1;
	int nPosEnd = -1;

	while( (nPosStart=csHtml.Find("<!--"))>-1 && (nPosEnd=csHtml.Find("-->"))>-1)
	{

		csHtml=csHtml.Left(nPosStart)+csHtml.Mid(nPosEnd+_tcslen("-->"));
	}  

}
int CStringUtil::CountCharacters(LPCTSTR lpcTxt, char chrToCount)
{
	int nCount=0;

	for(;*lpcTxt!='\0';lpcTxt++)
	{
		if(*lpcTxt==chrToCount)
			nCount++;
	}
	return nCount;
}
BOOL CStringUtil::IsNumber(LPCTSTR lpcTxt)
{
	if(*lpcTxt=='\0')
		return FALSE;
	BOOL bRet=TRUE;

	for(;*lpcTxt!='\0';lpcTxt++)
	{
		if(*lpcTxt<48 || *lpcTxt>57)
		{
			bRet=FALSE;
			break;
		}
	}
	return bRet;
}
int CStringUtil::CountDigits(LPCTSTR lpcTxt)
{
	int nCount=0;
	if(*lpcTxt=='\0')
		return nCount;

	for(;*lpcTxt!='\0';lpcTxt++)
	{
		if(*lpcTxt>=48 && *lpcTxt<=57)
		{
			nCount++;			
		}
	}
	return nCount;
}
BOOL CStringUtil::DoesContainDigit(LPCTSTR lpcTxt)
{
	if(*lpcTxt=='\0')
		return FALSE;
	BOOL bRet=FALSE;

	for(;*lpcTxt!='\0';lpcTxt++)
	{
		if(*lpcTxt>=48 && *lpcTxt<=57)
		{
			bRet=TRUE;
			break;
		}
	}
	return bRet;
}
BOOL CStringUtil::DoesContainAlphabet(LPCTSTR lpcTxt)
{
	if(*lpcTxt=='\0')
		return FALSE;
	BOOL bRet=FALSE;

	for(;*lpcTxt!='\0';lpcTxt++)
	{
		if( (*lpcTxt>64 && *lpcTxt<91) ||(*lpcTxt>96 && *lpcTxt<123))
		{
			bRet=TRUE;
			break;
		}
	}
	return bRet;
}
int CStringUtil::LastFindOf(const CString &csContent, LPCTSTR lpcFind)
{
	int nRet=-1,nPos=0;
	if(_tcslen(lpcFind)==0)
		return nRet;
	while( (nPos=csContent.Find(lpcFind,nPos))>-1)
	{
		nRet=nPos;
		nPos=nPos+1;
	}
	return nRet;
}
