// ListCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlDlg.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include <Afxdlgs.h>
#include "comutil.h"


#pragma comment(lib, "comsupp.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog

CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlDlg::IDD)
{
	//{{AFX_DATA_INIT(CListCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_iItemCount = 0;
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CListCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_LST_DELETE, OnLstDelete)
	ON_COMMAND(ID_LST_INSERT, OnLstInsert)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_VALIDATE, OnEndLabelEditVariableCriteria)
	ON_MESSAGE(WM_SET_ITEMS, PopulateComboList)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CListCtrlDlg::OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LINGSAVE, &CListCtrlDlg::OnButtonLingsave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CListCtrlDlg::OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_INDEX, &CListCtrlDlg::OnButtonIndex)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CListCtrlDlg::OnButtonAdd)
	ON_COMMAND(ID_XIU, &CListCtrlDlg::OnButtonXiu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg message handlers

BOOL CListCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	// Make the necessary initializations
	length = rect.Width();
	m_List.GetClientRect(&rect);
	m = 0;
	m_List.InsertColumn(m, "���", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 1, "����", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 2, "ѧ��", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 3, "�༶", LVCFMT_LEFT, 75);

	m_List.SetReadOnlyColumns(0);
	//m_List.SetComboColumns(1);

	CString strValidChars = "";
	m_List.SetValidEditCtrlCharacters(strValidChars);
	m_List.EnableVScroll(); 

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_REPORT);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListCtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CListCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListCtrlDlg::OnLstDelete() 
{
	// TODO: Add your command handler code here
	// Get the current selected item
	POSITION SelectionPos = m_List.GetFirstSelectedItemPosition();
	int iCurSel = -1;

	// Delete the selected item from the list control 
	while (NULL != SelectionPos)
	{
		SelectionPos = m_List.GetFirstSelectedItemPosition();
		iCurSel = m_List.GetNextSelectedItem(SelectionPos);
		m_List.DeleteItem(iCurSel);
	}
}

void CListCtrlDlg::OnLstInsert() 
{
	// TODO: Add your command handler code here
	// Insert a new row below the selected row or at the end
	CString strResource;
	strResource.Format("%d", ++m_iItemCount);

	int iCount = m_List.GetItemCount();

	int iRow = -1;

	POSITION SelectedItemPos = m_List.GetFirstSelectedItemPosition();
	int iIndex = -1;
	int iLastSelectedIndex = -1;

	while (SelectedItemPos)
	{
		iIndex = m_List.GetNextSelectedItem(SelectedItemPos);

		if ((LVIS_SELECTED == m_List.GetItemState(iIndex, LVIS_SELECTED)) && 
			(LVIS_FOCUSED == m_List.GetItemState(iIndex, LVIS_FOCUSED)))
		{
			iRow = iIndex;
		}
		m_List.SetItemState(iIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
	}


	if (-1 == iRow)
	{
		m_List.InsertItem(LVIF_TEXT | LVIF_STATE, iCount,
		strResource, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED, 0, 0);
	}
	else
	{
		m_List.InsertItem(LVIF_TEXT | LVIF_STATE, iRow,
		strResource, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED, 0, 0);
	}
}

void CListCtrlDlg::OnButtonXiu()
{
	// TODO:  �ڴ���������������
	::AfxMessageBox("�Ƿ��޸�", IDOK);
	CString strResource;
	strResource.Format("%d", ++m_iItemCount);

	int iCount = m_List.GetItemCount();

	int iRow = -1;

	POSITION SelectedItemPos = m_List.GetFirstSelectedItemPosition();
	int iIndex = -1;
	int iLastSelectedIndex = -1;

	while (SelectedItemPos)
	{
		iIndex = m_List.GetNextSelectedItem(SelectedItemPos);

		if ((LVIS_SELECTED == m_List.GetItemState(iIndex, LVIS_SELECTED)) &&
			(LVIS_FOCUSED == m_List.GetItemState(iIndex, LVIS_FOCUSED)))
		{
			iRow = iIndex;
		}
		m_List.SetItemState(iIndex, 0, LVIS_SELECTED | LVIS_FOCUSED);
	}


	if (-1 == iRow)
	{
		m_List.InsertItem(LVIF_TEXT | LVIF_STATE, iCount,
			strResource, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED, 0, 0);
	}
	else
	{
		m_List.InsertItem(LVIF_TEXT | LVIF_STATE, iRow,
			strResource, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED, 0, 0);
	}
}

void CListCtrlDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// Create the pop up menu
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_POPUP); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_List.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);

	*pResult = 0;
}

LRESULT CListCtrlDlg::OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)lParam;
	// TODO: Add your control notification handler code here
	
	if (wParam == IDC_LIST)
	{
		// Update the item text with the new text
		CString strUpdatedTxt = pDispInfo->item.pszText;  
		
		// Validate the format of the new string for the edit columns
		// If invalid then
		// Set pResult to 1 
		switch(pDispInfo->item.iSubItem)
		{
		case 0:
		case 1:
			break;
		default:
			{
				if (!strUpdatedTxt.IsEmpty()) 
				{
					// Get the left most non numeral characters
					// Get the remaining numerals
					// If the left most part does not contain the mandatory conditions 
					// Or the rest contains the mandatory conditions 
					// Display an error and set focus back onto the control
					int iFirstNumeralOccurrance = strUpdatedTxt.FindOneOf("");
					CString strNonNumerals = strUpdatedTxt.Left(iFirstNumeralOccurrance);
					CString strNumerals = strUpdatedTxt.Mid(iFirstNumeralOccurrance);
					
					strNonNumerals.TrimLeft(); 
					strNonNumerals.TrimRight();
					strNumerals.TrimLeft();
					strNumerals.TrimRight();  

					int iDecimalIndex = strNumerals.Find(".");
					
					if ((-1 != iDecimalIndex) && (iDecimalIndex != (strNumerals.GetLength() - 1)))  
					{
						iDecimalIndex = strNumerals.Find(".", iDecimalIndex + 1);
					}

					// Check that the condition is either
					// Not empty or "=" or "!=" or "<" or ">" or "<=" or ">="
					// The Numerals do not contain 
					// Space or more than 1 "." or any of the conditions
					if (
						(!strNonNumerals.IsEmpty()) || 
						(-1 != strNumerals.Find(" ")) ||
						(-1 != iDecimalIndex)
						)
					{
						AfxMessageBox("�����ʽ���ԣ����ݽ��ָ���"); 
						m_List.SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, "");
					}
					return 0;
				}
			}
			break;
		}
	}

	return 1;
}

LRESULT CListCtrlDlg::PopulateComboList(WPARAM wParam, LPARAM lParam)
{
	// Get the Combobox window pointer
	CComboBox* pInPlaceCombo = static_cast<CComboBox*> (GetFocus());

	// Get the inplace combbox top left
	CRect obWindowRect;

	pInPlaceCombo->GetWindowRect(&obWindowRect);
	
	CPoint obInPlaceComboTopLeft(obWindowRect.TopLeft()); 
	
	// Get the active list
	// Get the control window rect
	// If the inplace combobox top left is in the rect then
	// The control is the active control
	m_List.GetWindowRect(&obWindowRect);
	
	int iColIndex = wParam;
	
	CStringList* pComboList = reinterpret_cast<CStringList*>(lParam);
	pComboList->RemoveAll(); 

	if (obWindowRect.PtInRect(obInPlaceComboTopLeft)) 
	{
		if (1 == iColIndex)
		{
			pComboList->AddTail("��");
			pComboList->AddTail("Ů");
		}
	}
	
	return true;
	//return 0;
}


void CListCtrlDlg::OnButtonSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ж��б�����Ƿ��м�¼
	if (m_List.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("�б���û�м�¼��Ҫ���棡"));
		return;
	}
	else
	{
		if (AfxMessageBox("ȷ��Ҫ������?", MB_OKCANCEL) == IDOK)
		{
			/*CFileDialog FileDialog(FALSE, "xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Microsoft Excel(*.xls)|*.xls|�����ļ�(*.*)"), this);
			if (FileDialog.DoModal() != IDOK)
			{
				return;
			}*/
			CString stText;
			stText = "ѧ����Ϣ";

			CString cStrFile;//%d��%d��%d��%dʱ%d��%d��
			CTime m_time = CTime::GetCurrentTime();
			cStrFile.Format("C:\\" + stText + "-" + "%d��%d��%d��%dʱ%d��%d��.xls", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay(), m_time.GetHour(), m_time.GetMinute(),
				m_time.GetSecond());
			//CString cStrFile = FileDialog.GetPathName();  //ѡ�񱣴�·������  

			if (::PathFileExists(cStrFile))
				DeleteFile(cStrFile);

			COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			CApplication app; //Excel����  
			CWorkbooks books; //����������  
			CWorkbook book;  //������  
			CWorksheets sheets;  //����������  
			CWorksheet sheet; //��������  
			CRange range; //ʹ������  

			book.PrintPreview(_variant_t(false));

			if (!app.CreateDispatch(_T("Excel.Application")))//����IDispatch�ӿڶ���  
			{
				AfxMessageBox(_T("����ʧ�ܣ�"));
			}
			else
			{
				AfxMessageBox(_T("����ɹ���"));
			}
			books = app.get_Workbooks();
			book = books.Add(covOptional);

			sheets = book.get_Worksheets();
			sheet = sheets.get_Item(COleVariant((short)1));  //�õ���һ��������  

			CHeaderCtrl   *pmyHeaderCtrl = m_List.GetHeaderCtrl(); //��ȡ��ͷ  

			int   m_cols = pmyHeaderCtrl->GetItemCount(); //��ȡ����  
			int   m_rows = m_List.GetItemCount();  //��ȡ����  

			TCHAR     lpBuffer[256];

			HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;

			CString   colname;
			CString strTemp;

			int   iRow, iCol;
			for (iCol = 0; iCol < m_cols; iCol++)//���б�ı���ͷд��EXCEL   
			{
				GetCellName(1, iCol + 1, colname); //(colname���Ƕ�Ӧ����A1,B1,C1,D1)  

				range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
				pmyHeaderCtrl->GetItem(iCol, &hdi); //��ȡ��ͷÿ�е���Ϣ  
				range.put_Value2(COleVariant(hdi.pszText));  //����ÿ�е�����  

				int   nWidth = m_List.GetColumnWidth(iCol) / 6;

				//�õ���iCol+1�� 
				range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);

				//�����п�    
				range.put_ColumnWidth(_variant_t((long)nWidth));


			}
			range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
			range.put_RowHeight(_variant_t((long)50));//�����еĸ߶�   
			range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

			COleSafeArray   saRet; //COleSafeArray�������ڴ����������ͺ�ά�����������  
			DWORD   numElements[] = { m_rows, m_cols };       //����д������  
			saRet.Create(VT_BSTR, 2, numElements); //�������������  

			range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional); //��A2��ʼ  
			range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols)); //�������  

			long   index[2];

			for (iRow = 1; iRow <= m_rows; iRow++)//���б�����д��EXCEL   
			{
				for (iCol = 1; iCol <= m_cols; iCol++)
				{
					index[0] = iRow - 1;
					index[1] = iCol - 1;
					CString   szTemp;
					szTemp = m_List.GetItemText(iRow - 1, iCol - 1); //ȡ��m_list�ؼ��е�����  
					BSTR   bstr = szTemp.AllocSysString(); //The AllocSysString method alloscates a new BSTR string that is Automation compatible  
					saRet.PutElement(index, bstr); //��m_list�ؼ��е����ݷ���saRet
					SysFreeString(bstr);
				}
			}
			range.put_Value2(COleVariant(saRet)); //���õ������ݵ�saRet����ֵ������  
			book.SaveCopyAs(COleVariant(cStrFile)); //���浽cStrFile�ļ� 
			book.put_Saved(true);
			books.Close();

			//�ͷŶ��� 
			range.ReleaseDispatch();
			sheet.ReleaseDispatch();
			sheets.ReleaseDispatch();
			book.ReleaseDispatch();
			books.ReleaseDispatch();

			//����˳���ܱ�
			app.Quit();
			app.ReleaseDispatch();
		}
		else
		{
			return;
		}
	}

}


void CListCtrlDlg::OnButtonLingsave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ж��б�����Ƿ��м�¼
	if (m_List.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("�б���û�м�¼��Ҫ���棡"));
		return;
	}
	else
	{
		if (AfxMessageBox("ȷ��Ҫ������?", MB_OKCANCEL) == IDOK)
		{
			CFileDialog FileDialog(FALSE, "xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Microsoft Excel(*.xls)|*.xls|�����ļ�(*.*)"), this);
			if (FileDialog.DoModal() != IDOK)
			{
				return;
			}
			//CString stText;
			//stText = "ѧ����Ϣ";

			//CString cStrFile;//%d��%d��%d��%dʱ%d��%d��
			//CTime m_time = CTime::GetCurrentTime();
			//cStrFile.Format("C:\\" + stText + "-" + "%d��%d��%d��%dʱ%d��%d��.xls", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay(), m_time.GetHour(), m_time.GetMinute(),
			//	m_time.GetSecond());
			CString cStrFile = FileDialog.GetPathName();  //ѡ�񱣴�·������  

			if (::PathFileExists(cStrFile))
				DeleteFile(cStrFile);

			COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			CApplication app; //Excel����  
			CWorkbooks books; //����������  
			CWorkbook book;  //������  
			CWorksheets sheets;  //����������  
			CWorksheet sheet; //��������  
			CRange range; //ʹ������  

			book.PrintPreview(_variant_t(false));

			if (!app.CreateDispatch(_T("Excel.Application")))//����IDispatch�ӿڶ���  
			{
				AfxMessageBox(_T("����ʧ�ܣ�"));
			}
			else
			{
				AfxMessageBox(_T("����ɹ���"));
			}
			books = app.get_Workbooks();
			book = books.Add(covOptional);

			sheets = book.get_Worksheets();
			sheet = sheets.get_Item(COleVariant((short)1));  //�õ���һ��������  

			CHeaderCtrl   *pmyHeaderCtrl = m_List.GetHeaderCtrl(); //��ȡ��ͷ  

			int   m_cols = pmyHeaderCtrl->GetItemCount(); //��ȡ����  
			int   m_rows = m_List.GetItemCount();  //��ȡ����  

			TCHAR     lpBuffer[256];

			HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;

			CString   colname;
			CString strTemp;

			int   iRow, iCol;
			for (iCol = 0; iCol < m_cols; iCol++)//���б�ı���ͷд��EXCEL   
			{
				GetCellName(1, iCol + 1, colname); //(colname���Ƕ�Ӧ����A1,B1,C1,D1)  

				range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
				pmyHeaderCtrl->GetItem(iCol, &hdi); //��ȡ��ͷÿ�е���Ϣ  
				range.put_Value2(COleVariant(hdi.pszText));  //����ÿ�е�����  

				int   nWidth = m_List.GetColumnWidth(iCol) / 6;

				//�õ���iCol+1�� 
				range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);

				//�����п�    
				range.put_ColumnWidth(_variant_t((long)nWidth));


			}
			range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
			range.put_RowHeight(_variant_t((long)50));//�����еĸ߶�   
			range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

			COleSafeArray   saRet; //COleSafeArray�������ڴ����������ͺ�ά�����������  
			DWORD   numElements[] = { m_rows, m_cols };       //����д������  
			saRet.Create(VT_BSTR, 2, numElements); //�������������  

			range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional); //��A2��ʼ  
			range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols)); //�������  

			long   index[2];

			for (iRow = 1; iRow <= m_rows; iRow++)//���б�����д��EXCEL   
			{
				for (iCol = 1; iCol <= m_cols; iCol++)
				{
					index[0] = iRow - 1;
					index[1] = iCol - 1;
					CString   szTemp;
					szTemp = m_List.GetItemText(iRow - 1, iCol - 1); //ȡ��m_list�ؼ��е�����  
					BSTR   bstr = szTemp.AllocSysString(); //The AllocSysString method alloscates a new BSTR string that is Automation compatible  
					saRet.PutElement(index, bstr); //��m_list�ؼ��е����ݷ���saRet
					SysFreeString(bstr);
				}
			}
			range.put_Value2(COleVariant(saRet)); //���õ������ݵ�saRet����ֵ������  
			book.SaveCopyAs(COleVariant(cStrFile)); //���浽cStrFile�ļ� 
			book.put_Saved(true);
			books.Close();

			//�ͷŶ��� 
			range.ReleaseDispatch();
			sheet.ReleaseDispatch();
			sheets.ReleaseDispatch();
			book.ReleaseDispatch();
			books.ReleaseDispatch();

			//����˳���ܱ�
			app.Quit();
			app.ReleaseDispatch();
		}
		else
		{
			return;
		}
	}
}


void CListCtrlDlg::OnButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

		CListCtrlDlg::OnOK();
}


void CListCtrlDlg::OnButtonIndex()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	dlg.DoModal();
	for (int i = 0; i < m_List.GetItemCount(); i++ )
	{
		for (int j = 0; j <m_List.GetHeaderCtrl()->GetItemCount(); j++)
		{
			CString s = m_List.GetItemText(i, j); //i���У�j���� m_list�Ǹ�list control ����
			if (s == dlg.m_guanjianci)
			{
				char a[2], b[2];
				itoa(i + 1, a, 10);
				itoa(j + 1, b, 10);
				CString sum;
				sum.Format("%s��\n%s��\n%s", a, b, "ƥ��ɹ���");
				MessageBox(sum,"�ɹ�");
				break;
			}
		}
	}
}


void CListCtrlDlg::OnButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		dlg2.DoModal();
		m_List.InsertColumn(m + 6 , dlg2.m_lieming, LVCFMT_LEFT, 50);
		m++;
		//m_List.SetComboColumns(5);
}

void  CListCtrlDlg::GetCellName(int nRow, int nCol, CString &strName)
{
	int nSeed = nCol;
	CString strRow;
	char cCell = 'A' + nCol - 1;
	strName.Format(_T("%c"), cCell);
	strRow.Format(_T("%d "), nRow);
	strName += strRow;
}
