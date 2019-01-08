#pragma once
#include "StdAfx.h"
#include "afxwin.h"

// m_CSerachDlg �Ի���

class CSerachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerachDlg)

public:
	CSerachDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerachDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedExit();
	afx_msg void OnStnClickedUp();
	afx_msg void OnStnClickedDown();
	virtual BOOL OnInitDialog();

	void SetSerachInfo(const int nCount,const CString strKey);  //��ȡ������Ϣ
	void OnDestroy();      //���ٶԻ���

	CBrush m_brush;
	CFont  m_font;
private:
	CString m_iCount;   //��������
    CString m_KeyName;  //�����ؼ���
public:
	CStatic m_edit;
};
