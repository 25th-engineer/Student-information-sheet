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
	//  DDX_Text(pDX, IDC_EDIT_CHARU, m_charu);
	DDX_Control(pDX, IDC_EDIT_CHARU, m_charu);
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
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CListCtrlDlg::OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CListCtrlDlg::OnButtonOpen)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CListCtrlDlg::OnDblclkList)
	ON_WM_SIZE()
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
	m_charu.ShowWindow(SW_HIDE);
	// Make the necessary initializations
	length = rect.Width();
	m_List.GetClientRect(&rect);
	m = 0;
	//初始化列表框
	m_List.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	//显示字体的颜色
	m_List.SetTextColor(RGB(0, 0, 0));
	m_List.InsertColumn(m, "序号", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 1, "姓名", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 2, "学号", LVCFMT_LEFT, 75);
	m_List.InsertColumn(m + 3, "班级", LVCFMT_LEFT, 75);

	m_List.SetReadOnlyColumns(0);
	//m_List.SetComboColumns(1);

	CString strValidChars = "";
	m_List.SetValidEditCtrlCharacters(strValidChars);
	m_List.EnableVScroll(); 
	
	
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CRect rc;
	GetClientRect(&rc);//获取对话框客户区大小  
	GetDlgItem(IDC_BUTTON_OPEN)->ShowWindow(SW_HIDE);
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
	if (isiconic())
	{
		cpaintdc dc(this); // device context for painting

		sendmessage(wm_iconerasebkgnd, (wparam) dc.getsafehdc(), 0);

		// center icon in client rectangle
		int cxicon = getsystemmetrics(sm_cxicon);
		int cyicon = getsystemmetrics(sm_cyicon);
		crect rect;
		getclientrect(&rect);
		int x = (rect.width() - cxicon + 1) / 2;
		int y = (rect.height() - cyicon + 1) / 2;

		// draw the icon
		dc.drawicon(x, y, m_hicon);
	}
	else
	{
		cdialog::onpaint();
	}
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		CDialog::UpdateWindow(); //UpdateWindow一下
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
	// TODO:  在此添加命令处理程序代码
	if (IDYES == ::AfxMessageBox("是否修改", MB_YESNO))
	{
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
			iIndex++;
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
						AfxMessageBox("插入格式不对，数据将恢复！"); 
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
			pComboList->AddTail("男");
			pComboList->AddTail("女");
		}
	}
	
	return true;
	//return 0;
}


void CListCtrlDlg::OnButtonSave()
{
	// TODO:  在此添加控件通知处理程序代码
	//首先判断列表框中是否有记录
	if (m_List.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("列表中没有记录需要保存！"));
		return;
	}
	else
	{
		if (AfxMessageBox("确定要保存吗?", MB_OKCANCEL) == IDOK)
		{
			/*CFileDialog FileDialog(FALSE, "xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Microsoft Excel(*.xls)|*.xls|所有文件(*.*)"), this);
			if (FileDialog.DoModal() != IDOK)
			{
				return;
			}*/
			CString stText;
			stText = "学生信息";

			CString cStrFile;//%d年%d月%d日%d时%d分%d秒
			CTime m_time = CTime::GetCurrentTime();
			cStrFile.Format("C:\\" + stText + "-" + "%d年%d月%d日%d时%d分%d秒.xls", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay(), m_time.GetHour(), m_time.GetMinute(),
				m_time.GetSecond());
			//CString cStrFile = FileDialog.GetPathName();  //选择保存路径名称  

			if (::PathFileExists(cStrFile))
				DeleteFile(cStrFile);

			COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			CApplication app; //Excel程序  
			CWorkbooks books; //工作簿集合  
			CWorkbook book;  //工作表  
			CWorksheets sheets;  //工作簿集合  
			CWorksheet sheet; //工作表集合  
			CRange range; //使用区域  

			book.PrintPreview(_variant_t(false));

			if (!app.CreateDispatch(_T("Excel.Application")))//创建IDispatch接口对象  
			{
				AfxMessageBox(_T("保存失败！"));
			}
			else
			{
				AfxMessageBox(_T("保存成功！"));
			}
			books = app.get_Workbooks();
			book = books.Add(covOptional);

			sheets = book.get_Worksheets();
			sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表  

			CHeaderCtrl   *pmyHeaderCtrl = m_List.GetHeaderCtrl(); //获取表头  

			int   m_cols = pmyHeaderCtrl->GetItemCount(); //获取列数  
			int   m_rows = m_List.GetItemCount();  //获取行数  

			TCHAR     lpBuffer[256];

			HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;

			CString   colname;
			CString strTemp;

			int   iRow, iCol;
			for (iCol = 0; iCol < m_cols; iCol++)//将列表的标题头写入EXCEL   
			{
				GetCellName(1, iCol + 1, colname); //(colname就是对应表格的A1,B1,C1,D1)  
				range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
				pmyHeaderCtrl->GetItem(iCol, &hdi); //获取表头每列的信息  
				range.put_Value2(COleVariant(hdi.pszText));  //设置每列的内容  
				int   nWidth = m_List.GetColumnWidth(iCol) / 6;
				//得到第iCol+1列 
				range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);
				//设置列宽    
				range.put_ColumnWidth(_variant_t((long)nWidth));


			}
			range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
			range.put_RowHeight(_variant_t((long)50));//设置行的高度   
			range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

			COleSafeArray   saRet; //COleSafeArray类是用于处理任意类型和维数的数组的类  
			DWORD   numElements[] = { m_rows, m_cols };       //行列写入数组  
			saRet.Create(VT_BSTR, 2, numElements); //创建所需的数组  

			range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional); //从A2开始  
			range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols)); //表的区域  

			long   index[2];

			for (iRow = 1; iRow <= m_rows; iRow++)//将列表内容写入EXCEL   
			{
				for (iCol = 1; iCol <= m_cols; iCol++)
				{
					index[0] = iRow - 1;
					index[1] = iCol - 1;
					CString   szTemp;
					szTemp = m_List.GetItemText(iRow - 1, iCol - 1); //取得m_list控件中的内容  
					BSTR   bstr = szTemp.AllocSysString(); //The AllocSysString method alloscates a new BSTR string that is Automation compatible  
					saRet.PutElement(index, bstr); //把m_list控件中的内容放入saRet
					SysFreeString(bstr);
				}
			}
			range.put_Value2(COleVariant(saRet)); //将得到的数据的saRet数组值放入表格  
			book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件 
			book.put_Saved(true);
			books.Close();

			//释放对象 
			range.ReleaseDispatch();
			sheet.ReleaseDispatch();
			sheets.ReleaseDispatch();
			book.ReleaseDispatch();
			books.ReleaseDispatch();

			//调用顺序不能变
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
	// TODO:  在此添加控件通知处理程序代码
	//首先判断列表框中是否有记录
	if (m_List.GetItemCount() <= 0)
	{
		AfxMessageBox(_T("列表中没有记录需要保存！"));
		return;
	}
	else
	{
		if (AfxMessageBox("确定要保存吗?", MB_OKCANCEL) == IDOK)
		{
			CFileDialog FileDialog(FALSE, "xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Microsoft Excel(*.xls)|*.xls|所有文件(*.*)"), this);
			if (FileDialog.DoModal() != IDOK)
			{
				return;
			}
			//CString stText;
			//stText = "学生信息";

			//CString cStrFile;//%d年%d月%d日%d时%d分%d秒
			//CTime m_time = CTime::GetCurrentTime();
			//cStrFile.Format("C:\\" + stText + "-" + "%d年%d月%d日%d时%d分%d秒.xls", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay(), m_time.GetHour(), m_time.GetMinute(),
			//	m_time.GetSecond());
			CString cStrFile = FileDialog.GetPathName();  //选择保存路径名称  

			if (::PathFileExists(cStrFile))
				DeleteFile(cStrFile);

			COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			CApplication app; //Excel程序  
			CWorkbooks books; //工作簿集合  
			CWorkbook book;  //工作表  
			CWorksheets sheets;  //工作簿集合  
			CWorksheet sheet; //工作表集合  
			CRange range; //使用区域  

			book.PrintPreview(_variant_t(false));

			if (!app.CreateDispatch(_T("Excel.Application")))//创建IDispatch接口对象  
			{
				AfxMessageBox(_T("保存失败！"));
			}
			else
			{
				AfxMessageBox(_T("保存成功！"));
			}
			books = app.get_Workbooks();
			book = books.Add(covOptional);

			sheets = book.get_Worksheets();
			sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表  

			CHeaderCtrl   *pmyHeaderCtrl = m_List.GetHeaderCtrl(); //获取表头  

			int   m_cols = pmyHeaderCtrl->GetItemCount(); //获取列数  
			int   m_rows = m_List.GetItemCount();  //获取行数  

			TCHAR     lpBuffer[256];

			HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;

			CString   colname;
			CString strTemp;

			int   iRow, iCol;
			for (iCol = 0; iCol < m_cols; iCol++)//将列表的标题头写入EXCEL   
			{
				GetCellName(1, iCol + 1, colname); //(colname就是对应表格的A1,B1,C1,D1)  

				range = sheet.get_Range(COleVariant(colname), COleVariant(colname));
				pmyHeaderCtrl->GetItem(iCol, &hdi); //获取表头每列的信息  
				range.put_Value2(COleVariant(hdi.pszText));  //设置每列的内容  

				int   nWidth = m_List.GetColumnWidth(iCol) / 6;

				//得到第iCol+1列 
				range.AttachDispatch(range.get_Item(_variant_t((long)(iCol + 1)), vtMissing).pdispVal, true);

				//设置列宽    
				range.put_ColumnWidth(_variant_t((long)nWidth));


			}
			range = sheet.get_Range(COleVariant(_T("A1 ")), COleVariant(colname));
			range.put_RowHeight(_variant_t((long)50));//设置行的高度   
			range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

			COleSafeArray   saRet; //COleSafeArray类是用于处理任意类型和维数的数组的类  
			DWORD   numElements[] = { m_rows, m_cols };       //行列写入数组  
			saRet.Create(VT_BSTR, 2, numElements); //创建所需的数组  

			range = sheet.get_Range(COleVariant(_T("A2 ")), covOptional); //从A2开始  
			range = range.get_Resize(COleVariant((short)m_rows), COleVariant((short)m_cols)); //表的区域  

			long   index[2];

			for (iRow = 1; iRow <= m_rows; iRow++)//将列表内容写入EXCEL   
			{
				for (iCol = 1; iCol <= m_cols; iCol++)
				{
					index[0] = iRow - 1;
					index[1] = iCol - 1;
					CString   szTemp;
					szTemp = m_List.GetItemText(iRow - 1, iCol - 1); //取得m_list控件中的内容  
					BSTR   bstr = szTemp.AllocSysString(); //The AllocSysString method alloscates a new BSTR string that is Automation compatible  
					saRet.PutElement(index, bstr); //把m_list控件中的内容放入saRet
					SysFreeString(bstr);
				}
			}
			range.put_Value2(COleVariant(saRet)); //将得到的数据的saRet数组值放入表格  
			book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件 
			book.put_Saved(true);
			books.Close();

			//释放对象 
			range.ReleaseDispatch();
			sheet.ReleaseDispatch();
			sheets.ReleaseDispatch();
			book.ReleaseDispatch();
			books.ReleaseDispatch();

			//调用顺序不能变
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
	// TODO:  在此添加控件通知处理程序代码

		CListCtrlDlg::OnOK();
}


void CListCtrlDlg::OnButtonIndex()
{
	// TODO:  在此添加控件通知处理程序代码
	dlg.DoModal();
	for (int i = 0; i < m_List.GetItemCount(); i++ )
	{
		for (int j = 0; j <m_List.GetHeaderCtrl()->GetItemCount(); j++)
		{
			CString s = m_List.GetItemText(i, j); //i是行，j是列 m_list是个list control 对象
			if (s == dlg.m_guanjianci)
			{
				char a[2], b[2];
				itoa(i + 1, a, 10);
				itoa(j + 1, b, 10);
				CString sum;
				sum.Format("%s行\n%s列\n%s", a, b, "匹配成功！");
				MessageBox(sum,"成功");
				break;
			}
		}
	}
}


void CListCtrlDlg::OnButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
		dlg2.DoModal();
		m_List.InsertColumn(m + 6 , dlg2.m_lieming, LVCFMT_LEFT, 50);
		m++;
		//m_List.SetComboColumns(5);
}

void CListCtrlDlg::OnButtonDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	dlg3.DoModal();
	int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.

	for (int i = 0; i < nColumnCount; i++)
	{
		HDITEM hdi;
		TCHAR  lpBuffer[256];
		bool   fFound = false;
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = 256;
		m_List.GetHeaderCtrl()->GetItem(i, &hdi);//i列的名
		if (dlg3.m_delete == hdi.pszText)
		{
			m_List.DeleteColumn(i);
		}
	}
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



void CListCtrlDlg::OnButtonOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,//TRUE或FALSE。TRUE为打开文件；FALSE为保存文件
		_T("xls"), //为缺省的扩展名
		_T("FileList"), //为显示在文件名组合框的编辑框的文件名，一般可选NULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//为对话框风格，一般为OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,即隐藏只读选项和覆盖已有文件前提示。 
		_T("Excel 文件(*.xls)|*.xls||")//为下拉列表枢中显示文件类型
		);
	dlg.m_ofn.lpstrTitle = _T("导入数据");

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	//获得文件路径名
	strFilePath = dlg.GetPathName();
	//判断文件是否已经存在，存在则打开文件
	DWORD dwRe = GetFileAttributes(strFilePath);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else return;
	CDatabase db;//数据库库需要包含头文件 #include <afxdb.h>
	CString sDriver = _T("MICROSOFT EXCEL DRIVER (*.XLS)"); // Excel驱动
	CString sSql, arr[14];

	sSql.Format(_T("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s"), sDriver, strFilePath, strFilePath);
	if (!db.OpenEx(sSql, CDatabase::noOdbcDialog))//连接数据源DJB．xls
	{
		MessageBox(_T("打开EXCEL文件失败!", "错误"));
		return;
	}
	//打开EXCEL表
	CRecordset pset(&db);
	m_List.DeleteAllItems();
	sSql.Format(_T("SELECT * FROM [DSO_DX$]"));
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	while (!pset.IsEOF())
	{
		pset.GetFieldValue(_T("M序号"), arr[0]);//前面字段必须与表中的相同，否则出错。
		pset.GetFieldValue(_T("A支柱A编号"), arr[1]);
		pset.GetFieldValue(_T("B支柱B编号"), arr[2]);
		pset.GetFieldValue(_T("HcA支柱A承力索高度"), arr[3]);
		pset.GetFieldValue(_T("HcB支柱B承力索高度"), arr[4]);
		pset.GetFieldValue(_T("HjA杆A导高"), arr[5]);
		pset.GetFieldValue(_T("HjB杆B导高"), arr[6]);
		pset.GetFieldValue(_T("L跨距"), arr[7]);
		pset.GetFieldValue(_T("a1杆A超高"), arr[8]);
		pset.GetFieldValue(_T("a2杆B超高"), arr[9]);
		pset.GetFieldValue(_T("R曲线半径"), arr[10]);
		pset.GetFieldValue(_T("R0竖曲线半径"), arr[11]);
		pset.GetFieldValue(_T("Hw曲线外轨超高值"), arr[12]);
		pset.GetFieldValue(_T("Y吊弦长度"), arr[13]);

		int count = m_List.GetItemCount();//插入到ListCtrl中
		m_List.InsertItem(count, arr[0]);
		m_List.SetItemText(count, 1, arr[1]);
		m_List.SetItemText(count, 2, arr[2]);
		m_List.SetItemText(count, 3, arr[3]);
		m_List.SetItemText(count, 4, arr[4]);
		m_List.SetItemText(count, 5, arr[5]);
		m_List.SetItemText(count, 6, arr[6]);
		m_List.SetItemText(count, 7, arr[7]);
		m_List.SetItemText(count, 8, arr[8]);
		m_List.SetItemText(count, 9, arr[9]);
		m_List.SetItemText(count, 10, arr[10]);
		m_List.SetItemText(count, 11, arr[11]);
		m_List.SetItemText(count, 12, arr[12]);
		m_List.SetItemText(count, 13, arr[13]);
		pset.MoveNext();
	}
	db.Close();

	MessageBox(_T("Excel数据成功导入系统!"), "导    入");
}


void CListCtrlDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_Row = pNMListView->iItem;
	m_Col = pNMListView->iSubItem;

	if (pNMListView->iItem == -1)    //选择空白处，添加一行，并设置焦点为最后一行，第二列  
	{
		m_Row = m_List.GetItemCount();
		strTemp.Format(_T("%d"), m_Row + 1);
		m_List.InsertItem(m_Row, strTemp);
		m_List.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_List.EnsureVisible(m_Row, FALSE);
		m_iItemCount++;
		//m_Col = 1;  
	}

	if (m_Col != 0) // 选择子项  
	{
		m_List.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);
		m_charu.SetParent(&m_List);
		m_charu.MoveWindow(rc);
		m_charu.SetWindowText(m_List.GetItemText(m_Row, m_Col));
		m_charu.ShowWindow(SW_HIDE);
		m_charu.SetFocus();//设置Edit焦点  
		m_charu.ShowCaret();//显示光标  
		m_charu.SetSel(0, -1);

	}
	*pResult = 0;
}


void CListCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO:  在此处添加消息处理程序代码
	if (nType != SIZE_MINIMIZED)
	{

		int a[9] = {  IDC_LIST, IDC_EDIT_CHARU, IDC_BUTTON_ADD, IDC_BUTTON_DELETE, IDC_BUTTON_EXIT, IDC_BUTTON_INDEX,
			IDC_BUTTON_LINGSAVE, IDC_BUTTON_OPEN, IDC_BUTTON_SAVE
		};
		int i;
		for (i = 0; i < 9; i++)
			ReSizes(a[i], m_rect, cx, cy);

		

		GetClientRect(&m_rect);//将变化后的对话框大小设为旧大小
	}
}


//======================================
//设置对话框尺寸函数
//======================================
void CListCtrlDlg::ReSizes(int idc, CRect client, int x, int y)
{
	CWnd *pWin;
	pWin = GetDlgItem(idc);//获取控件句柄
	if (pWin)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
	{
		CRect Editrect;//获取控件变化前大小
		pWin->GetWindowRect(&Editrect);
		ScreenToClient(&Editrect);//将控件大小转换为在对话框中的区域坐标
		//x/client.Width()为对话框在横向的变化比例

		Editrect.left = Editrect.left*x / client.Width();//调整控件大小
		Editrect.right = Editrect.right*x / client.Width();
		Editrect.top = Editrect.top*y / client.Height();
		Editrect.bottom = Editrect.bottom*y / client.Height();
		pWin->MoveWindow(Editrect);//调整控件大小

	}
}