#pragma once


// CDropListBox dialog

class CDropListBox : public CListBox
{
	DECLARE_DYNAMIC(CDropListBox)

public:
	CDropListBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDropListBox();

	afx_msg void PreSubclassWindow();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
// Dialog Data
	enum { IDD = IDC_LIST_FILES };

protected:

	DECLARE_MESSAGE_MAP()
};
