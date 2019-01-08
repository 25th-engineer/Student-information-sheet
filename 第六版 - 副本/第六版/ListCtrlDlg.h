
#include "ComboListCtrl.h"// ListCtrlDlg.h : header file
#include "InPlaceEdit.h"
#include "afxcmn.h"
#include <afxwin.h>
#include <windows.h>
#include <vector>
#include "KeyDlg.h"
#include "ChaRuDlg.h"
#include "DeleteLieDlg.h"
#include "SerachDlg.h"
#include "FilterDlg.h"
#include "StdAfx.h"
//

#if !defined(AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_)
#define AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog
//struct StuductInfo
//{
//   CString strNumber;   //序号
//   CString strName;     //姓名
//   CString strID;       //学号
//   CString strClass;    //班级
//   CString strGrade;    //年级
//   CString strSex;      //性别
//};



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
	//HICON m_hIcon;
	HICON m_hIcon1;
	// Generated message map functions
	//{{AFX_MSG(CListCtrlDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL OnInitDialog();
	afx_msg void OnLstDelete();
	afx_msg void OnLstInsert();
	afx_msg void OnLstMinisizeScreen();
	afx_msg void OnLstMaxisizeScreen();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PopulateComboList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLingsave();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonIndex();
	afx_msg void OnButtonAdd();
	afx_msg void ReadVersion(CString& strVersion, CString& strCopyriht);
	afx_msg void DisplayAuthor();
	
	DECLARE_MESSAGE_MAP()

public:
	int m_iItemCount;
	void  GetCellName(int nRow, int nCol, CString &strName);//获得excel单元名
	int length;
	CRect rect;
	char* m_strCopyriht;
	int m;
	int m_Row, m_Col;
	CKeyDlg dlg;
	CChaRuDlg dlg2;
	CDeleteLieDlg dlg3;
    CSerachDlg*  pDlg;

	CRect m_rect;
	CEdit m_charu;

	int  iSerachIndex;
	std::pair<int,int>m_Index;                  //检索当前位置
	std::vector<std::pair<int,int>>m_vecSerach; //检索的全部位置数据	


	//查询条件
	CString* pColName;
	CMap<CString,LPCSTR,CString*,CString*>mapAllData;     //所有数据,用于列表控件显示
	CMap<CString,LPCSTR,CString*,CString*>mapCheckData;   //查询条件后的数据,用于列表控控件显示

	bool CheackConditions(std::vector<CString>&vecTemp,int nColIndex[]);  // 判断查询条件内容是否符合列名
	void QueryInfo(std::vector<CString>&vecDataTemp,int nColIndex[]);          //条件查询数据
	void SaveData();           //保存所有数据
	void ShowFirstSerach();     //显示检索第一个 

	afx_msg void OnButtonXiu();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonOpen();
//	CString m_charu;
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	void ReSizes(int idc, CRect client, int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonFilter();
	void SortFirstColumn();

protected:
	afx_msg LRESULT OnUserUpSerach(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserDownSerach(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonImport();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDLG_H__714B2AD4_9E96_43B7_BB6A_C176A6BD68AA__INCLUDED_)
