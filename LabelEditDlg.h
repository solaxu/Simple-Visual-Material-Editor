#pragma once


// CLabelEditDlg �Ի���

class CLabelEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLabelEditDlg)

public:
	CLabelEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLabelEditDlg();

	CString text;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABEL_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
