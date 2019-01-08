// KeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "KeyDlg.h"
#include "afxdialogex.h"


// CKeyDlg 对话框

IMPLEMENT_DYNAMIC(CKeyDlg, CDialogEx)

CKeyDlg::CKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyDlg::IDD, pParent)
	, m_keywords(_T(""))
{

}

CKeyDlg::~CKeyDlg()
{
}

void CKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KeyCI, m_keywords);
}


BEGIN_MESSAGE_MAP(CKeyDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CKeyDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyDlg 消息处理程序


void CKeyDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CKeyDlg::OnBnClickedButton1()
{
	CString strKey = _T("");
	((CEdit*)GetDlgItem(IDC_EDIT_KeyCI))->GetWindowText(strKey);
	if(strKey.IsEmpty())
	{
		AfxMessageBox(_T("输入内容不能为空!"));
	}
	else
	{
	  CDialogEx::OnOK();
	}
}
