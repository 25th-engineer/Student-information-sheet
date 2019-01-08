#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void SetRowHeight(int nHeight);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) ;
protected:
	DECLARE_MESSAGE_MAP()
	int m_nRowHeight;
	CFont m_font;
};


