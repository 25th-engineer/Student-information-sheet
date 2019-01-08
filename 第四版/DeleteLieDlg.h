#pragma once


// CDeleteLieDlg 对话框

class CDeleteLieDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteLieDlg)

public:
	CDeleteLieDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeleteLieDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_delete;
};
