#pragma once


// CGuanjianDlg �Ի���

class CGuanjianDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGuanjianDlg)

public:
	CGuanjianDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGuanjianDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_guanjianci;
};
