#pragma once

#include <vector>

// CInoutputDlg 对话框
using std::vector;

class CInoutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInoutputDlg)

public:
	CInoutputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInoutputDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INOUT_DLG };
#endif

public:
	vector<CString> M_NAMES;
	vector<CString> M_TYPES;
	vector<CString> M_SEMANTICS;
	INT m_count = 0;
protected:
	vector<CEdit*> m_names;
	vector<CComboBox*> m_types;
	vector<CComboBox*> m_semantics;

	BOOL OnInitDialog();

	void GetAllCtrls();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
};
