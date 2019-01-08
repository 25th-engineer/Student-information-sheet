// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()


void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)  
{  
    lpMeasureItemStruct->itemHeight = m_nRowHeight;  
}  


// CMyListCtrl 消息处理程序
void CMyListCtrl::SetRowHeight(int nHeight)
{
	m_nRowHeight = nHeight;
	//如果没有下面的代码，设置并不能奏效
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	TCHAR lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDrawItemStruct->itemID ; 
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));

	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	{
		if ( nCol > 0 ) 
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left ; 
		}

		// Get the text 
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));

		CDC* pDC;
		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT)) ; 
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		}
		else
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW)) ;
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)) ; 
		}
		CFont font;                               //文本字体
		LOGFONT lf;
		GetFont()->GetLogFont( &lf );
		lf.lfHeight = abs(lf.lfHeight) + 2;
		lf.lfWeight = FW_BOLD;
		pDC->SelectObject(GetFont()->m_hObject);

  /*      pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));*/

		UINT   uFormat    = DT_LEFT ;

		::DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
			&lpDrawItemStruct->rcItem, uFormat) ;
      
		pDC->SelectStockObject(SYSTEM_FONT) ;
	}
}
