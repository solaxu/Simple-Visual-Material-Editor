#pragma once


// CSamplerTexDlg �Ի���

class CSamplerTexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSamplerTexDlg)

public:
	CSamplerTexDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSamplerTexDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLER_DLG };
#endif

public:

	DWORD AddrU, AddrV, AddrW;
	DWORD FilterMag, FilterMin, FilterMip;
	DWORD MaxMipLvl;
	DWORD BorderR, BorderG, BorderB, BorderA;
	CString TexPath;

protected:

	BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSamplerTexSelector();
	afx_msg void OnBnClickedOk();
};
