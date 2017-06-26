#pragma once


// CSamplerTexDlg 对话框

class CSamplerTexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSamplerTexDlg)

public:
	CSamplerTexDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSamplerTexDlg();

// 对话框数据
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

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSamplerTexSelector();
	afx_msg void OnBnClickedOk();
};
