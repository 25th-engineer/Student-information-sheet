// GuanjianDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "GuanjianDlg.h"
#include "afxdialogex.h"


// CGuanjianDlg �Ի���

IMPLEMENT_DYNAMIC(CGuanjianDlg, CDialogEx)

CGuanjianDlg::CGuanjianDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGuanjianDlg::IDD, pParent)
	, m_guanjianci(_T(""))
{

}

CGuanjianDlg::~CGuanjianDlg()
{
}

void CGuanjianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GUANJIANCI, m_guanjianci);
}


BEGIN_MESSAGE_MAP(CGuanjianDlg, CDialogEx)
END_MESSAGE_MAP()


// CGuanjianDlg ��Ϣ�������
