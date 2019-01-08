// FilterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg �Ի���

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilterDlg::IDD, pParent)
{
	iCount = 3;
	mapFilter.RemoveAll();
}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListFilter);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CFilterDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CFilterDlg::OnDblclkList2)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CFilterDlg::OnKillfocusEdit1)
	ON_BN_CLICKED(IDCANCEL, &CFilterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFilterDlg ��Ϣ�������


void CFilterDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(JudgeData())
	{
	   CDialogEx::OnOK();
	}
}


//��ʼ���ؼ�
void CFilterDlg::InitCtrl()
{  
	m_edit.ShowWindow(SW_HIDE);


	//m_ListFilter.SetExtendedStyle(LVS_EX_GRIDLINES); 
	//CImageList   m_imageList; 
	//m_imageList.Create(1,20,ILC_COLOR24,1,1);   //1��ͼƬ��20�Ǹ߶� 
	//m_ListFilter.SetImageList(&m_imageList,LVSIL_SMALL); 

	//������չ���
	DWORD dwStyle = m_ListFilter.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ListFilter.SetExtendedStyle(dwStyle);   

	//��������
	CRect rect;
	m_ListFilter.GetClientRect(&rect);
	int nWidth = rect.Width()/3;
	m_ListFilter.InsertColumn(0,_T("����1"),LVCFMT_CENTER,nWidth);
	m_ListFilter.InsertColumn(1,_T("����2"),LVCFMT_CENTER,nWidth);
	m_ListFilter.InsertColumn(2,_T("����3"),LVCFMT_CENTER,nWidth);

	m_ListFilter.InsertItem(0,_T(""));
	m_ListFilter.SetItemText(0,1,_T(""));
	m_ListFilter.SetItemText(0,2,_T(""));
	m_ListFilter.SetItemText(0,3,_T(""));

	m_ListFilter.InsertItem(1,_T(""));
	m_ListFilter.SetItemText(1,1,_T(""));
	m_ListFilter.SetItemText(1,2,_T(""));
	m_ListFilter.SetItemText(1,3,_T(""));

}    

BOOL CFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//��������
void CFilterDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	iCount++;
	CRect rect;
	m_ListFilter.GetClientRect(&rect);

	int nWidth = rect.Width()/iCount;	
	CString strTemp;
	strTemp.Format("����%d",iCount);

	m_ListFilter.InsertColumn(iCount-1,strTemp,LVCFMT_CENTER,nWidth);

	for(UINT i=0;i<iCount;i++)
	{
	   m_ListFilter.SetColumnWidth(i,nWidth);
	}
}


void CFilterDlg::OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CRect rc;  
    CString strTemp;  
    NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;  
    m_Row = pNMListView->iItem;  
    m_Col = pNMListView->iSubItem;  

	if (pNMListView->iItem == -1)    //ѡ��հ״������һ�У������ý���Ϊ���һ�У��ڶ���  
	{
	return;
	}

    if (m_Col >= 0) // ѡ������  
    {  
        m_ListFilter.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);  
        m_edit.SetParent(&m_ListFilter);  
        m_edit.MoveWindow(rc);  
        m_edit.SetWindowText(m_ListFilter.GetItemText(m_Row, m_Col));  
        m_edit.ShowWindow(SW_SHOW);  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(0, -1);//ȫѡ  
    }  
	*pResult = 0;
}


void CFilterDlg::OnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;  
    m_edit.GetWindowText(str);  
    m_ListFilter.SetItemText(m_Row, m_Col, str);  
    m_edit.ShowWindow(SW_HIDE);  

	m_arrary[m_Col][m_Row] = str;
}


BOOL CFilterDlg::JudgeData()     //�ж�����
{   
	BOOL bFlag = TRUE;
  
	for(UINT i=0;i<iCount;i++)
	{
		if(m_arrary[i][0] != _T(""))
		{
			if(m_arrary[i][1] == _T(""))
			{   
				mapFilter.RemoveAll();
				CString strTemp;
				strTemp.Format(_T("��������%d����Ϊ��,����������"),i+1);				
				AfxMessageBox(strTemp);
				bFlag = FALSE;
				break;
			}
			else
			{
			   CString strKey   = m_arrary[i][0]; 
  	           CString strValue = m_arrary[i][1];
			   mapFilter.SetAt(strKey,strValue);
			}
		}
		else
		{
			bFlag = FALSE;
			CString strTemp;
			strTemp.Format(_T("��������%d����Ϊ��,����������"),i+1);	
			break;
		}
	}
	return bFlag;
}

void CFilterDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mapFilter.RemoveAll();
	CDialogEx::OnCancel();
}
