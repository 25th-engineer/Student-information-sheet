// CSerachDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "ListCtrl.h"
#include "SerachDlg.h"
#include "afxdialogex.h"


// CSerachDlg �Ի���

IMPLEMENT_DYNAMIC(CSerachDlg, CDialogEx)

CSerachDlg::CSerachDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerachDlg::IDD, pParent)
{
    m_iCount = "-1";   //��������
    m_KeyName = "NULL";  //�����ؼ���
}

CSerachDlg::~CSerachDlg()
{
}

void CSerachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIP, m_edit);
}


BEGIN_MESSAGE_MAP(CSerachDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_EXIT, &CSerachDlg::OnStnClickedExit)
	ON_STN_CLICKED(IDC_UP, &CSerachDlg::OnStnClickedUp)
	ON_STN_CLICKED(IDC_DOWN, &CSerachDlg::OnStnClickedDown)
END_MESSAGE_MAP()


// CSerachDlg ��Ϣ�������


HBRUSH CSerachDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if (pWnd->GetDlgCtrlID() == IDC_EXIT || pWnd->GetDlgCtrlID() == IDC_UP || pWnd->GetDlgCtrlID() == IDC_DOWN || pWnd->GetDlgCtrlID() == IDC_TIP)
    {
   //   pDC->SetBkColor(RGB(0,255,0));    //����ɫΪ��ɫ
       pDC->SetTextColor(RGB(255, 0, 0));//����Ϊ��ɫ
       pDC->SelectObject(&m_font);       //����Ϊ15�����壬�����п�
       return m_brush;
    }

	return hbr;
}

void CSerachDlg::OnDestroy()
{
   CDialogEx::OnDestroy();
   delete this;
}

void CSerachDlg::OnStnClickedExit()
{
	ShowWindow(SW_HIDE);
}

//���ϼ���
void CSerachDlg::OnStnClickedUp()
{
	::PostMessage(::AfxGetMainWnd()->m_hWnd,WM_USER_UP_SERACH,0,0); 
}

//���¼���
void CSerachDlg::OnStnClickedDown()
{
	::PostMessage(::AfxGetMainWnd()->m_hWnd,WM_USER_DOWN_SERACH,0,0);
}



BOOL CSerachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_font.CreatePointFont(150,"�����п�");//����15�����壬�����п�
   // m_brush.CreateSolidBrush(RGB(0,255,0));//��ˢΪ��ɫ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

 //��ȡ������Ϣ
void CSerachDlg::SetSerachInfo(const int nCount, const CString strKey) 
{

	if(nCount >= 0)
	{
		m_iCount.Format("%d",nCount);
	}

    m_KeyName = strKey;

	CString strInfo = "������ ";
	strInfo += m_iCount;
	strInfo += "(��ֵ: ";
	strInfo += strKey;
	strInfo += " ) ��";
	m_edit.SetWindowTextA(strInfo);
	UpdateData(false);
}

