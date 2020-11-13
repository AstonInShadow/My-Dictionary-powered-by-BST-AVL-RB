
// MFCECDictionaryDlg.cpp: 实现文件
//
#include <atlbase.h>
#include "pch.h"
#include "framework.h"
#include "MFCECDictionary.h"
#include "MFCECDictionaryDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "MyNode.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCECDictionaryDlg 对话框



CMFCECDictionaryDlg::CMFCECDictionaryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCECDICTIONARY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCECDictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITINBOX, M_INBOX);
	DDX_Control(pDX, IDC_LISTOUTLIST, M_OUTLIST);
	DDX_Control(pDX, IDC_CHECKMAP, m_MapOrNot);
	DDX_Control(pDX, IDC_CHECK, m_RouteorNot);
}

BEGIN_MESSAGE_MAP(CMFCECDictionaryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATDICTIONARY, &CMFCECDictionaryDlg::OnBnClickedCreatdictionary)
	ON_BN_CLICKED(IDC_BSTSEARCH, &CMFCECDictionaryDlg::OnBnClickedBstsearch)
	ON_EN_CHANGE(IDC_EDITINBOX, &CMFCECDictionaryDlg::OnEnChangeEditinbox)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCECDictionaryDlg::OnBnClickedButtonINOFF)
	ON_BN_CLICKED(IDC_AVLSEARCH, &CMFCECDictionaryDlg::OnBnClickedAvlsearch)
	ON_BN_CLICKED(IDC_RBSEARCH, &CMFCECDictionaryDlg::OnBnClickedRbsearch)
	ON_BN_CLICKED(IDC_CHECKMAP, &CMFCECDictionaryDlg::OnBnClickedCheckmap)
	ON_BN_CLICKED(IDC_CHECK, &CMFCECDictionaryDlg::OnBnClickedCheckROUTE)
END_MESSAGE_MAP()


// CMFCECDictionaryDlg 消息处理程序

BOOL CMFCECDictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	DWORD dwStyle = M_OUTLIST.GetExtendedStyle();
	dwStyle = LVS_EX_FULLROWSELECT;
	dwStyle = LVS_EX_GRIDLINES;
	M_OUTLIST.SetExtendedStyle(dwStyle);
	M_OUTLIST.InsertColumn(0, _T("单词"), LVCFMT_LEFT, 200);
	M_OUTLIST.InsertColumn(1, _T("释义"), LVCFMT_LEFT, 750);
	return TRUE;  
	// 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCECDictionaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCECDictionaryDlg::OnPaint()
{
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
		dc.DrawIcon(x, y, m_hIcon);
		// 绘制图标

	}
	else
	{
		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCECDictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCECDictionaryDlg::OnBnClickedCreatdictionary()
{
	CMFCECDictionaryDlg::DataInPut();
	/*for (it = M_Buffer.begin(); it != M_Buffer.end(); it++)
	{
		M_Map.insert(map<string, string>::value_type(it->key, it->val));
	}*/
}
void CMFCECDictionaryDlg::OnBnClickedBstsearch()
{
	if (m_RouteOrN) {
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowText(m_str);
		string str;
		str = CT2A(m_str);
		BSTSearch(tree.root, str);
		CString temp;
		for (int i = 0; i < show.GetSize(); i++)
		{
			temp = show.GetAt(i).english.c_str();
			M_OUTLIST.InsertItem(i, temp);
			temp.Empty();
			temp = show.GetAt(i).explain.c_str();
			M_OUTLIST.SetItemText(i, 1, temp);
			temp.Empty();
		}
		CString strout;
		strout.Format(_T("比较了%d次"), show.GetSize());
		AfxMessageBox(strout);
	}
	else {
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowText(m_str);
		string str;
		str = CT2A(m_str);
		BSTSearch(tree.root, str);
		CString temp;
		int ij = show.GetSize()-1;
		temp = show.GetAt(ij).english.c_str();
		M_OUTLIST.InsertItem(0, temp);
		temp.Empty();
		temp = show.GetAt(ij).explain.c_str();
		M_OUTLIST.SetItemText(0, 1, temp);
		temp.Empty();
	}
}
void CMFCECDictionaryDlg::DataInPut()
{
	
	
		string value;
		ifstream infile("C:\\Users\\86159\\Desktop\\EnWords.csv");
		string line;
		getline(infile, line);
		while (getline(infile, line))
		{
			pairs Temp;
			string temp1;
			string temp2;
			istringstream sin(line);
			getline(sin, temp1, '"');
			getline(sin, temp1, '"');
			Temp.english = temp1;
			getline(sin, temp2, ',');
			getline(sin, temp2);
			//temp3=(temp2.c_str());
			//CMFCECDictionaryDlg::UTFtoASIC(temp3);
			Temp.explain = temp2;
			m_arr.Add(Temp);
			M_Map.insert(pair<string, string>(temp1, temp2));
		}
		infile.close();
		CString temp;
		M_OUTLIST.DeleteAllItems();
		int n = m_arr.GetSize();
		CreatBST(n, n / 2, tree.root);
		CString tempN;
		tempN.Format(_T("成功读取了目标文件中%d个词条"), n);
		AfxMessageBox(tempN);

	
}
void CMFCECDictionaryDlg::CreatBST(int len, int pos, BinTreeNode*& p)
{
	if (len == 2)
	{
		p = new BinTreeNode(m_arr.GetAt(pos));
		p->leftChild = new BinTreeNode(m_arr.GetAt(pos - 1));
		p->rightChild = NULL;
		return;
	}
	if (len == 1)
	{
		p = new BinTreeNode(m_arr.GetAt(pos));
		p->leftChild = NULL;
		p->rightChild = NULL;
		return;
	}
	p = new BinTreeNode(m_arr.GetAt(pos));
	CreatBST(len / 2, pos - len/ 2 + (len / 2) / 2, p->leftChild);
	CreatBST(len - len / 2 - 1, pos + 1 + (len / 2 - 1) / 2, p->rightChild);
}
void CMFCECDictionaryDlg::BSTSearch(BinTreeNode* ptr, string Keys)
{
	show.RemoveAll();
	while (ptr != NULL)
	{
		if (Keys > ptr->data.english)
		{
			show.Add(ptr->data);
			ptr = ptr->rightChild;
		}
		else if (Keys < ptr->data.english)
		{
			show.Add(ptr->data);
			ptr = ptr->leftChild;
		}
		else
		{
			show.Add(ptr->data);
			break;
		}
	}
	if (ptr == NULL)
	{
		AfxMessageBox(_T("找不到该元素"));
	}
	/*Node* p = R;
	while (p!= NULL)
	{
		if (Keys < p->key)
		{
			Node EXChange;
			EXChange.key = p->key;
			EXChange.val = p->val;
			M_ShowBuffer.push_back(EXChange);
			p = p->left;
		}
		else if (Keys > p->key)
		{
			Node EXChange;
			EXChange.key = p->key;
			EXChange.val = p->val;
			M_ShowBuffer.push_back(EXChange);
			p = p->right;
		}
		else
		{
			Node EXChange;
			EXChange.key = p->key;
			EXChange.val = p->val;
			M_ShowBuffer.push_back(EXChange);
			break;
		}
	}
	if (p == NULL)
	{
		AfxMessageBox(_T("找不到该元素"));
	}*/
}
void CMFCECDictionaryDlg::OnEnChangeEditinbox()
{
	if (m_MapOrN) {
		CString m_str;
		M_INBOX.GetWindowTextA(m_str);
		string str;
		str = CT2A(m_str);
		M_OUTLIST.DeleteAllItems();
		map<string, string>::iterator pos;
		pos = M_Map.lower_bound(str);
		show.RemoveAll();
		if (str != "" && pos != M_Map.end())
		{
			CString temp;
			int j = 0;
			for (pos; pos != M_Map.end(); pos++)
			{
				if (pos->first.find(str) == -1)
					break;
				temp = pos->first.c_str();
				M_OUTLIST.InsertItem(j, temp);
				temp.Empty();
				temp = pos->second.c_str();
				M_OUTLIST.SetItemText(j, 1, temp);
				temp.Empty();
				j++;
			}
		}
	}
	else;
}


void CMFCECDictionaryDlg::OnBnClickedButtonINOFF()
{
	M_OUTLIST.DeleteAllItems();
	CString m_str;
	M_INBOX.GetWindowText(m_str);
	string str;
	str = CT2A(m_str);
	int i = 0;
	// TODO: 在此添加控件通知处理程序代码
	for (i = 0; i < m_arr.GetSize(); i++)
	{

		if (m_arr.GetAt(i).english == str)
		{
			CString temp;
			temp.Format(_T("比较了%d次"), i + 1);
			AfxMessageBox(temp);
			temp.Empty();
			temp = m_arr.GetAt(i).english.c_str();
			M_OUTLIST.InsertItem(0, temp);
			temp.Empty();
			temp = m_arr.GetAt(i).explain.c_str();
			M_OUTLIST.SetItemText(0, 1, temp);
			temp.Empty();
			break;
		}
	}
	if (i == m_arr.GetSize())

		AfxMessageBox(_T("找不到该元素"));
}


void CMFCECDictionaryDlg::UTFtoASIC(CString& strUTF8)
{
		/*USES_CONVERSION;
		char* strutf8 = W2A(strUTF8);
		UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strutf8, -1, NULL, NULL);
		WCHAR* wszBuffer = new WCHAR[nLen + 1];
		nLen = MultiByteToWideChar(CP_UTF8, NULL, strutf8, -1, wszBuffer, nLen);
		wszBuffer[nLen] = 0;
		nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
		CHAR* szBuffer = new CHAR[nLen + 1];
		nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
		szBuffer[nLen] = 0;
		string szbuffer = szBuffer;
		strUTF8 = szbuffer.c_str();
		delete[]szBuffer;
		delete[]wszBuffer;*/
		/*int nLen = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCTSTR)strUTF8, -1, NULL, 0);
		unsigned short* wszANSI = new unsigned short[nLen + 1];
		memset(wszANSI, 0, nLen * 2 + 2);
		nLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8, -1, wszANSI, nLen);
		nLen = WideCharToMultiByte(CP_ACP, 0, wszANSI, -1, NULL, 0, NULL, NULL);
		char* szANSI = new char[nLen + 1];
		memset(szANSI, 0, nLen + 1);
		WideCharToMultiByte(CP_ACP, 0, wszANSI, -1, szANSI, nLen, NULL, NULL);
		strUTF8 = szANSI;
		delete wszANSI;
		delete szANSI;
		*/
}


void CMFCECDictionaryDlg::OnBnClickedAvlsearch()
{
	AVLTree Atree;
	for (int i = 0; i < m_arr.GetSize(); i++)
		Atree.insert(Atree.root, m_arr.GetAt(i));
	if (m_RouteOrN) {
		string str;
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowTextA(m_str);
		str = CT2A(m_str);
		BSTSearch(Atree.root, str);
		CString temp;
		for (int i = 0; i < show.GetSize(); i++)
		{
		temp = show.GetAt(i).english.c_str();
		M_OUTLIST.InsertItem(i, temp);
		temp.Empty();
		temp = show.GetAt(i).explain.c_str();
		M_OUTLIST.SetItemText(i, 1, temp);
		temp.Empty();
		}
		CString strout;
		strout.Format("比较了%d次", show.GetSize());
		AfxMessageBox(strout);
	}
	else {
		string str;
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowTextA(m_str);
		str = CT2A(m_str);
		BSTSearch(Atree.root, str);
		CString temp;
		int ij = show.GetSize()-1;
		temp = show.GetAt(ij).english.c_str();
		M_OUTLIST.InsertItem(0, temp);
		temp.Empty();
		temp = show.GetAt(ij).explain.c_str();
		M_OUTLIST.SetItemText(0, 1, temp);
		temp.Empty();
	}
}


void CMFCECDictionaryDlg::OnBnClickedRbsearch()
{
	RBTree Rtree;
	for (int i = 0; i < m_arr.GetSize(); i++)
		Rtree.insert(m_arr.GetAt(i));
	if (m_RouteOrN) {
		string str;
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowTextA(m_str);
		str = CT2A(m_str);
		RBSearch(Rtree.mRoot, str);
		CString temp;
		for (int i = 0; i < show.GetSize(); i++)
		{
			temp = show.GetAt(i).english.c_str();
			M_OUTLIST.InsertItem(i, temp);
			temp.Empty();
			temp = show.GetAt(i).explain.c_str();
			M_OUTLIST.SetItemText(i, 1, temp);
			temp.Empty();
		}
		CString strout;
		strout.Format("比较了%d次", show.GetSize());
		AfxMessageBox(strout);
	}
	else {
		string str;
		M_OUTLIST.DeleteAllItems();
		CString m_str;
		M_INBOX.GetWindowTextA(m_str);
		str = CT2A(m_str);
		RBSearch(Rtree.mRoot, str);
		CString temp;
		int ij = show.GetSize() - 1;
		temp = show.GetAt(ij).english.c_str();
		M_OUTLIST.InsertItem(0, temp);
		temp.Empty();
		temp = show.GetAt(ij).explain.c_str();
		M_OUTLIST.SetItemText(0, 1, temp);
		temp.Empty();
	}
}


void CMFCECDictionaryDlg::RBSearch(RBTNode* ptr, string str)
{
	// TODO: 在此处添加实现代码
	show.RemoveAll();
	while (ptr != NULL)
	{
		if (str > ptr->key.english)
		{
			show.Add(ptr->key);
			ptr = ptr->right;
		}
		else if (str < ptr->key.english)
		{
			show.Add(ptr->key);
			ptr = ptr->left;
		}
		else
		{
			show.Add(ptr->key);
			break;
		}
	}
	if (ptr == NULL)
	{
		AfxMessageBox("找不到该元素");
	}
}


void CMFCECDictionaryDlg::OnBnClickedCheckmap()
{
	int state = ((CButton*)GetDlgItem(IDC_CHECKMAP))->GetCheck();
	if (state == 1) {
		m_MapOrN = TRUE;
		M_OUTLIST.DeleteAllItems();
		CMFCECDictionaryDlg::OnEnChangeEditinbox();
	}
	else
	{
		m_MapOrN = FALSE;
		M_OUTLIST.DeleteAllItems();
		CMFCECDictionaryDlg::OnEnChangeEditinbox();
	}
}


void CMFCECDictionaryDlg::OnBnClickedCheckROUTE()
{
	int state = ((CButton*)GetDlgItem(IDC_CHECK))->GetCheck();
	if (state == 1) {
		m_RouteOrN = TRUE;
		M_OUTLIST.DeleteAllItems();
	}
	else
	{
		m_RouteOrN = FALSE;
		M_OUTLIST.DeleteAllItems();
	}
}
