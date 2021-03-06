
// DictionaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dictionary.h"
#include "DictionaryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CDictionaryDlg dialog



CDictionaryDlg::CDictionaryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DICTIONARY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDictionaryDlg::~CDictionaryDlg() {
	delete m_dic;
	delete m_label;
	m_FontLabel.DeleteObject();
	m_fontLabel90.DeleteObject();
}

void CDictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDictionaryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_KEY_TEXT, &CDictionaryDlg::OnEnChangeKeyText)
	ON_BN_CLICKED(IDC_LOADDATA_BUTTON, &CDictionaryDlg::OnBnClickedLoadDataBtn)
	ON_BN_CLICKED(IDC_SAVEDATA_BUTTON, &CDictionaryDlg::OnBnClickedSaveDataBtn)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CDictionaryDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_EDIT_BUTTON, &CDictionaryDlg::OnBnClickedEditBtn)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, &CDictionaryDlg::OnBnClickedRemoveBtn)
END_MESSAGE_MAP()


// CDictionaryDlg message handlers

BOOL CDictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowPos(NULL, 0, 0, 525, 400, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_FontLabel.CreatePointFont(180, _T("Arial Blod"));
	m_label = (CStatic *)GetDlgItem(IDC_TITLE_STRING);
	m_label->SetFont(&m_FontLabel);

	m_loadDataBtn.Create(_T("Load data"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 10, 100, 30), this, IDC_LOADDATA_BUTTON);
	m_saveDataBtn.Create(_T("Save data"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(110, 10, 200, 30), this, IDC_SAVEDATA_BUTTON);
	m_addBtn.Create(_T("Add"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(210, 10, 300, 30), this, IDC_ADD_BUTTON);
	m_editBtn.Create(_T("Edit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(310, 10, 400, 30), this, IDC_EDIT_BUTTON);
	m_removeBtn.Create(_T("Remove"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(410, 10, 500, 30), this, IDC_REMOVE_BUTTON);
	
	//CBitmap m_editBmp;
	//m_editBmp.LoadBitmapW(IDB_EDIT);
	//m_editBtn->SetBitmap(m_editBmp);

	m_fontButton.CreatePointFont(100, _T("Arial"));
	m_loadDataBtn.SetFont(&m_fontButton);
	m_saveDataBtn.SetFont(&m_fontButton);
	m_addBtn.SetFont(&m_fontButton);
	m_editBtn.SetFont(&m_fontButton);
	m_removeBtn.SetFont(&m_fontButton);

	m_wordLabel.Create(_T("Word"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(10, 105, 100, 120), this);
	m_keyText.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(10, 120, 500, 170), this, IDC_KEY_TEXT);

	m_definitionLabel.Create(_T("Definition"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(10, 185, 100, 200), this);
	m_valueText.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_VSCROLL, CRect(10, 200, 500, 350), this, IDC_VALUE_TEXT);

	//m_valueText.SetReadOnly(TRUE);

	m_fontLabel90.CreatePointFont(90, _T("Arial"));
	m_wordLabel.SetFont(&m_fontLabel90);
	m_definitionLabel.SetFont(&m_fontLabel90);

	if (!m_toolTip.Create(this)) {
		TRACE0("Unable to create the ToolTip!");
	}
	else {
		m_toolTip.AddTool(&m_loadDataBtn, _T("Load data from a file."));
		m_toolTip.AddTool(&m_saveDataBtn, _T("Store current data in a file."));
		m_toolTip.AddTool(&m_addBtn, _T("Enter word and definiton, after that click \"Add\" to add new word."));
		m_toolTip.AddTool(&m_editBtn, _T("Enter word and definiton, after that click \"Edit\" to edit word."));
		m_toolTip.AddTool(&m_removeBtn, _T("Enter word and then click \"Remove\" to remove word."));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDictionaryDlg::PreTranslateMessage(MSG *pMsg) {
	m_toolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

string CSToString(CString cs) {
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(cs);
	// construct a std::string using the LPCSTR input
	std::string strStd(pszConvertedAnsiString);
	return strStd;
}

bool CDictionaryDlg::OnFileOpen(string &pathName) {
	// szFilters is a text string that includes two file name filters:
	// "*.txt" for "Text Document Files" and "*.*' for "All Files."
	TCHAR szFilters[] = _T("Text Document Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg(TRUE, _T("txt"), _T("*.txt"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		pathName = CSToString(fileDlg.GetPathName());

		// Implement opening and reading file in here.
		return true;

		//Change the window's title to the opened file's title.
		//CString fileName = fileDlg.GetFileTitle();

		//SetWindowText(fileName);
	}
	else {
		return false;
	}
}

bool CDictionaryDlg::OnFileSave(string &pathName) {
	char strFilter[] = { "Text Files (*.txt)|*.txt|" };

	CFileDialog FileDlg(FALSE, CString(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CString(strFilter));

	if (FileDlg.DoModal() == IDOK)
	{
		pathName = CSToString(FileDlg.GetPathName());
		return true;
	}
	return false;
}

void CDictionaryDlg::OnBnClickedLoadDataBtn() {
	string pathName;
	bool ret = OnFileOpen(pathName);
	if (!ret) return;
	ret = m_dic->loadData(pathName.c_str());
	if (ret == true) {
		MessageBox(_T("Load data done."), _T("Info"), MB_ICONINFORMATION);
	}
	else {
		MessageBox(_T("Can't open data file."), _T("Info"), MB_ICONINFORMATION);
	}
}

void CDictionaryDlg::OnBnClickedSaveDataBtn() {
	string pathName;
	bool ret = OnFileSave(pathName);
	if (!ret) return;
	ret = m_dic->saveData(pathName.c_str());
	if (ret == true) {
		MessageBox(_T("Data saved."), _T("Info"), MB_ICONINFORMATION);
	}
	else {
		MessageBox(_T("Can't open data file."), _T("Info"), MB_ICONINFORMATION);
	}
}

void CDictionaryDlg::OnBnClickedAddBtn() {
	CString key;
	m_keyText.GetWindowTextW(key);
	CString value;
	m_valueText.GetWindowTextW(value);
	m_dic->add(CSToString(key), CSToString(value));
	m_keyText.Clear();
	m_valueText.Clear();
}

void CDictionaryDlg::OnBnClickedEditBtn() {
	CString key;
	m_keyText.GetWindowTextW(key);
	CString value;
	m_valueText.GetWindowTextW(value);
	m_dic->edit(CSToString(key), CSToString(value));
	m_keyText.Clear();
	m_valueText.Clear();
}

void CDictionaryDlg::OnBnClickedRemoveBtn() {
	CString key;
	m_keyText.GetWindowTextW(key);
	m_dic->remove(CSToString(key));
	m_keyText.Clear();
	m_valueText.Clear();
}

void CDictionaryDlg::OnEnChangeKeyText() {
	CString key;
	m_keyText.GetWindowTextW(key);
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(key);
	// construct a std::string using the LPCSTR input
	std::string value(pszConvertedAnsiString);
	value = m_dic->search(value);
	m_valueText.SetWindowTextW(CString(value.c_str()));
}

void CDictionaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDictionaryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CDictionaryDlg::OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_TITLE_STRING)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
	}

	return hbr;
}

