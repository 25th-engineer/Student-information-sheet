#pragma once


// CChaRuDlg �Ի���

class CChaRuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChaRuDlg)

public:
	CChaRuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChaRuDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_lieming;
};
