#pragma once


// CKeyDlg 对话框

class CKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyDlg)

public:
	CKeyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKeyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_keywords;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
