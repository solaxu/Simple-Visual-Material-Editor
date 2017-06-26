#pragma once


// CFloatLabelDlg �Ի���

class CFloatLabelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloatLabelDlg)

public:
	CFloatLabelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFloatLabelDlg();

	float value;
	float M_MIN;
	float M_MAX;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLOAT_VALUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeFltMin();
	afx_msg void OnEnChangeFltMax();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawFltSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
