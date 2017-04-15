// DropListBox.cpp : implementation file
//

#include "stdafx.h"
#include "UnixTimeStampConvertor.h"
#include "DropListBox.h"


// CDropListBox dialog

IMPLEMENT_DYNAMIC(CDropListBox, CListBox)

CDropListBox::CDropListBox(CWnd* pParent /*=NULL*/)
: CListBox()
{

}

CDropListBox::~CDropListBox()
{
}


//	ON_LBN_SELCHANGE(IDC_LIST_FILES, &CUnixTimeStampConvertorDlg::OnLbnSelchangeListFiles)
BEGIN_MESSAGE_MAP(CDropListBox, CListBox)
    ON_WM_CREATE()
    ON_WM_DROPFILES()
END_MESSAGE_MAP()
// CDropListBox message handlers

// CDropListBox message handlers
int CDropListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListBox::OnCreate(lpCreateStruct) == -1)
        return -1;

    ::DragAcceptFiles(m_hWnd, TRUE);

    return 0;
}

void CDropListBox::OnDropFiles(HDROP hDropInfo)
{
        CString sFile;
    char *s=sFile.GetBufferSetLength(255);
    // Get number of files
    int numFiles=DragQueryFile(hDropInfo,0xFFFFFFFF,s,255); 
    sFile.ReleaseBuffer(); 
    for(int i=0;i<numFiles;i++)
    {
        s=sFile.GetBufferSetLength(255);
        DragQueryFile(hDropInfo,i,s,255);  // Get filename using the index
		CListBox::AddString(sFile);
        sFile.ReleaseBuffer();
		
    } 

    CListBox::OnDropFiles(hDropInfo);
}

void CDropListBox::PreSubclassWindow()
{
    ::DragAcceptFiles(m_hWnd, TRUE);

    CListBox::PreSubclassWindow();
}