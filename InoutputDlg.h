#pragma once

#include <vector>

// CInoutputDlg �Ի���
using std::vector;

class CInoutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInoutputDlg)

public:
	CInoutputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInoutputDlg();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
};
