#pragma once
#include "StdAfx.h"
#include "afxwin.h"

// m_CSerachDlg 对话框

class CSerachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerachDlg)

public:
	CSerachDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerachDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedExit();
	afx_msg void OnStnClickedUp();
	afx_msg void OnStnClickedDown();
	virtual BOOL OnInitDialog();

	void SetSerachInfo(const int nCount,const CString strKey);  //获取检索信息
	void OnDestroy();      //销毁对话框

	CBrush m_brush;
	CFont  m_font;
private:
	CString m_iCount;   //检索项数
    CString m_KeyName;  //检索关键字
public:
	CStatic m_edit;
};
