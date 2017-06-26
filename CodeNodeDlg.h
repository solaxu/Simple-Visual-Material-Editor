#pragma once

#include "LexState.h"
// CCodeNodeDlg 对话框

struct AutoCompListNode
{
	AutoCompListNode* _links[128];
	WCHAR _c;
	std::vector<CString> _words;

	AutoCompListNode() :_c(_T('\0'))
	{
		for (int i = 0; i < 128; ++i)
			_links[i] = NULL;
	}
};

struct FuncBlock
{
	SHLSLToken* m_tk = NULL;
	vector<SHLSLToken*> m_papams;
	vector<SHLSLToken*> m_paramTypes;
	vector<SHLSLToken*> m_ids;
	SHLSLToken* m_ret = NULL;
	vector<FuncBlock*> m_caller;
};



class CCodeNodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCodeNodeDlg)

public:
	CCodeNodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCodeNodeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODE_NODE_DLG };
#endif

public:
	CRichEditCtrl* m_richCtrl;
	CString m_code;	// 代码
	DWORD m_lineCount = 0;
	DWORD m_cartIndex = 0;
	BOOL m_InitDraw = TRUE;
	CString m_filePath;
	AutoCompListNode* m_autoComp = NULL;
	DWORD m_curLexemBegin = 0;
protected:

	DWORD m_timer;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void ColorText(BOOL bAll);

	BOOL OnInitDialog();

	AutoCompListNode* CreateBackAutoCompleteList(std::vector<SHLSLToken>& stream);

	BOOL PreTranslateMessage(MSG* pMsg);

	void DestroyAutoCompTree();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeCodeEdit();
	afx_msg void OnBnClickedOpenCode();
	afx_msg void OnEnUpdateCodeEdit();
	afx_msg void OnEnSetfocusCodeEdit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};