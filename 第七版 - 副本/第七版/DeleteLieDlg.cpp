// DeleteLieDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "DeleteLieDlg.h"
#include "afxdialogex.h"


// CDeleteLieDlg �Ի���

IMPLEMENT_DYNAMIC(CDeleteLieDlg, CDialogEx)

CDeleteLieDlg::CDeleteLieDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeleteLieDlg::IDD, pParent)
	, m_delete(_T(""))
{

}

CDeleteLieDlg::~CDeleteLieDlg()
{
}

void CDeleteLieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_delete);
}


BEGIN_MESSAGE_MAP(CDeleteLieDlg, CDialogEx)
END_MESSAGE_MAP()


// CDeleteLieDlg ��Ϣ�������
