#pragma once


// CDeleteLieDlg �Ի���

class CDeleteLieDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteLieDlg)

public:
	CDeleteLieDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteLieDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_delete;
};
