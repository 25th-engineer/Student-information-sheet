// CSerachDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "ListCtrl.h"
#include "SerachDlg.h"
#include "afxdialogex.h"


// CSerachDlg 对话框

IMPLEMENT_DYNAMIC(CSerachDlg, CDialogEx)

CSerachDlg::CSerachDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerachDlg::IDD, pParent)
{
    m_iCount = "-1";   //检索项数
    m_KeyName = "NULL";  //检索关键字
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


// CSerachDlg 消息处理程序


HBRUSH CSerachDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_EXIT || pWnd->GetDlgCtrlID() == IDC_UP || pWnd->GetDlgCtrlID() == IDC_DOWN || pWnd->GetDlgCtrlID() == IDC_TIP)
    {
   //   pDC->SetBkColor(RGB(0,255,0));    //背景色为绿色
       pDC->SetTextColor(RGB(255, 0, 0));//文字为红色
       pDC->SelectObject(&m_font);       //文字为15号字体，华文行楷
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

//向上检索
void CSerachDlg::OnStnClickedUp()
{
	::PostMessage(::AfxGetMainWnd()->m_hWnd,WM_USER_UP_SERACH,0,0); 
}

//向下检索
void CSerachDlg::OnStnClickedDown()
{
	::PostMessage(::AfxGetMainWnd()->m_hWnd,WM_USER_DOWN_SERACH,0,0);
}



BOOL CSerachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_font.CreatePointFont(150,"华文行楷");//代表15号字体，华文行楷
   // m_brush.CreateSolidBrush(RGB(0,255,0));//画刷为绿色

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

 //获取检索信息
void CSerachDlg::SetSerachInfo(const int nCount, const CString strKey) 
{

	if(nCount >= 0)
	{
		m_iCount.Format("%d",nCount);
	}

    m_KeyName = strKey;

	CString strInfo = "检索到 ";
	strInfo += m_iCount;
	strInfo += "(键值: ";
	strInfo += strKey;
	strInfo += " ) 项";
	m_edit.SetWindowTextA(strInfo);
	UpdateData(false);
}

