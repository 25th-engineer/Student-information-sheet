
#include "ComboListCtrl.h"// ListCtrlDlg.h : header file
#include "InPlaceEdit.h"
#include "afxcmn.h"
#include <afxwin.h>
#include <windows.h>
#include "GuanjianDlg.h"
#include "ChaRuDlg.h"
#include "DeleteLieDlg.h"
//

#if !defined(AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_)
#define AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog

class CListCtrlDlg : public CDialog
{
// Construction
public:
	CListCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListCtrlDlg)
	enum { IDD = IDD_LISTCTRL_DIALOG };
	CComboListCtrl m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListCtrlDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL OnInitDialog();
	afx_msg void OnLstDelete();
	afx_msg void OnLstInsert();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PopulateComboList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLingsave();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonIndex();
	afx_msg void OnButtonAdd();
	DECLARE_MESSAGE_MAP()

public:
	int m_iItemCount;
	void  GetCellName(int nRow, int nCol, CString &strName);//获得excel单元名
	int length;
	CRect rect;
	int m;
	CGuanjianDlg dlg;
	CChaRuDlg dlg2;
	CDeleteLieDlg dlg3;

	afx_msg void OnButtonXiu();
	afx_msg void OnButtonDelete();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_)
