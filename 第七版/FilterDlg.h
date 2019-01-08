#pragma once
#include "MylistCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"
// CFilterDlg 对话框

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilterDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	
	CEdit m_edit;
	CMyListCtrl m_ListFilter;   // 筛选条件列表
	UINT iCount;              //条件个数
	int m_Row;                //行数
	int m_Col;                //列数
	CString m_arrary[10][2];
	CRect m_rect;
	CFont m_Font;
public:
	
	CMap<CString,LPCTSTR,CString,LPCTSTR>mapFilter;

	void InitCtrl();           //初始化控件
	void SetCtrlFont();            //设置字体大小
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnBnClickedCancel();
	BOOL JudgeData();     //判断数据

};
