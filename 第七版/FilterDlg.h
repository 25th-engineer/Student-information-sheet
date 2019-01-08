#pragma once
#include "MylistCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"
// CFilterDlg �Ի���

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilterDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	
	CEdit m_edit;
	CMyListCtrl m_ListFilter;   // ɸѡ�����б�
	UINT iCount;              //��������
	int m_Row;                //����
	int m_Col;                //����
	CString m_arrary[10][2];
	CRect m_rect;
	CFont m_Font;
public:
	
	CMap<CString,LPCTSTR,CString,LPCTSTR>mapFilter;

	void InitCtrl();           //��ʼ���ؼ�
	void SetCtrlFont();            //���������С
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnBnClickedCancel();
	BOOL JudgeData();     //�ж�����

};
