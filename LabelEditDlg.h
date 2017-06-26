#pragma once


// CLabelEditDlg 对话框

class CLabelEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLabelEditDlg)

public:
	CLabelEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLabelEditDlg();

	CString text;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABEL_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
