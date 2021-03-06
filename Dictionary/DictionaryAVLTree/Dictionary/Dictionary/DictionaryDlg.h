
// DictionaryDlg.h : header file
//

#pragma once

#include "Process.h"

#define IDC_KEY_TEXT 1
#define IDC_VALUE_TEXT 2
#define IDC_LOADDATA_BUTTON 3
#define IDC_SAVEDATA_BUTTON 4
#define IDC_ADD_BUTTON 5
#define IDC_EDIT_BUTTON 6
#define IDC_REMOVE_BUTTON 7
#define IDC_WORDLABEL_STRING 8
#define IDC_DEFINITIONLABEL_STRING 9

// CDictionaryDlg dialog
class CDictionaryDlg : public CDialogEx
{
	// Construction
public:
	CDictionaryDlg(CWnd* pParent = nullptr);	// standard constructor
	~CDictionaryDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CEdit m_keyText;
	CEdit m_valueText;
	Dictionary *m_dic = new Dictionary;
	CButton m_loadDataBtn;
	CButton m_saveDataBtn;
	CButton m_addBtn;
	CButton m_editBtn;
	CButton m_removeBtn;
	CStatic *m_label;
	CToolTipCtrl m_toolTip;
	CStatic m_wordLabel;
	CStatic m_definitionLabel;
	CFont m_FontLabel;
	CFont m_fontLabel90;
	CFont m_fontButton;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	BOOL PreTranslateMessage(MSG *pMsg);
	bool OnFileOpen(string&);
	bool OnFileSave(string&);
	afx_msg void OnEnChangeKeyText();
	afx_msg void OnBnClickedLoadDataBtn();
	afx_msg void OnBnClickedSaveDataBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedRemoveBtn();
};
