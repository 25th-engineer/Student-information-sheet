// ChaRuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ChaRuDlg.h"
#include "afxdialogex.h"


// CChaRuDlg �Ի���

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


// CChaRuDlg ��Ϣ�������


void CChaRuDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
