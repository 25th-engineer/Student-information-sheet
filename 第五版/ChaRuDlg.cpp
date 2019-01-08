// ChaRuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ChaRuDlg.h"
#include "afxdialogex.h"


// CChaRuDlg 对话框

IMPLEMENT_DYNAMIC(CChaRuDlg, CDialogEx)

CChaRuDlg::CChaRuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChaRuDlg::IDD, pParent)
	, m_lieming(_T(""))
{

}

CChaRuDlg::~CChaRuDlg()
{
}

void CChaRuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_lieming);
}


BEGIN_MESSAGE_MAP(CChaRuDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CChaRuDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CChaRuDlg 消息处理程序


void CChaRuDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
