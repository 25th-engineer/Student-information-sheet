#pragma once


// CGuanjianDlg 对话框

class CGuanjianDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGuanjianDlg)

public:
	CGuanjianDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGuanjianDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_guanjianci;
};
