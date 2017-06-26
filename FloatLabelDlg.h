#pragma once


// CFloatLabelDlg 对话框

class CFloatLabelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloatLabelDlg)

public:
	CFloatLabelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFloatLabelDlg();

	float value;
	float M_MIN;
	float M_MAX;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLOAT_VALUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeFltMin();
	afx_msg void OnEnChangeFltMax();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawFltSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
