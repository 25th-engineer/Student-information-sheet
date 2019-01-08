#pragma once


// CChaRuDlg 对话框

class CChaRuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChaRuDlg)

public:
	CChaRuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChaRuDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_lieming;
};
