// CodeNodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "CodeNodeDlg.h"
#include "afxdialogex.h"
#include "HLSLLexer.h"
#include <xutility>
#include <algorithm>


// CCodeNodeDlg 对话框

IMPLEMENT_DYNAMIC(CCodeNodeDlg, CDialogEx)

CCodeNodeDlg::CCodeNodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CODE_NODE_DLG, pParent),m_timer(10)
{

}

CCodeNodeDlg::~CCodeNodeDlg()
{
	DestroyAutoCompTree();
}

void CCodeNodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCodeNodeDlg, CDialogEx)
	ON_BN_CLICKED(IDCODEOK, &CCodeNodeDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_CODE_EDIT, &CCodeNodeDlg::OnEnChangeCodeEdit)
	ON_BN_CLICKED(IDC_OPEN_CODE, &CCodeNodeDlg::OnBnClickedOpenCode)
	ON_EN_UPDATE(IDC_CODE_EDIT, &CCodeNodeDlg::OnEnUpdateCodeEdit)
	ON_EN_SETFOCUS(IDC_CODE_EDIT, &CCodeNodeDlg::OnEnSetfocusCodeEdit)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BOOL CCodeNodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_richCtrl = (CRichEditCtrl*)GetDlgItem(IDC_CODE_EDIT);

	CEdit* filePath = (CEdit*)GetDlgItem(IDC_CODE_PATH);
	filePath->SetWindowText(m_filePath);

	DWORD mask = m_richCtrl->GetEventMask();
	mask |= ENM_CHANGE;
	mask |= ENM_UPDATE;
	m_richCtrl->SetEventMask(mask);

	CHARFORMAT2W cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.dwEffects = ~CFE_AUTOCOLOR;
	cf.yHeight = 16 * 16;
	wcscpy(cf.szFaceName, _T("Arial"));//设置字体 
	m_richCtrl->SetDefaultCharFormat(cf);

	TEXTMETRIC        tmText;
	CRect            rtClient;

	m_richCtrl->GetClientRect(&rtClient);
	DWORD rcHeight = rtClient.Height();

 	GetTextMetrics(m_richCtrl->GetDC()->GetSafeHdc(), &tmText);
 	DWORD nLineHeight = tmText.tmHeight + tmText.tmExternalLeading + 1;
	m_lineCount = rcHeight / nLineHeight;

	m_InitDraw = TRUE;

	m_richCtrl->SetWindowText(m_code);

	SetTimer(m_timer, 500, NULL);
	return 1;
}

// CCodeNodeDlg 消息处理程序


void CCodeNodeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
	KillTimer(m_timer);
	m_InitDraw = TRUE;
	return;
}

void CCodeNodeDlg::ColorText(BOOL bAll)
{
	DWORD _1stLine = m_richCtrl->GetFirstVisibleLine();
	DWORD _1stChar = m_richCtrl->LineIndex(_1stLine);
	DWORD _lastLine = m_richCtrl->GetLineCount() - 1;
	if (_1stLine + m_lineCount + 2 < _lastLine)
		_lastLine = _1stLine + m_lineCount + 2;
	DWORD _lastChar = m_richCtrl->LineIndex(_lastLine) + m_richCtrl->LineLength(_lastLine) - 1;

	auto stream = CHLSLLexer::_Lexer->m_tokenStream;

	CHARFORMAT2W cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.dwEffects = ~CFE_AUTOCOLOR;
	cf.yHeight = 16 * 16;
	wcscpy(cf.szFaceName, _T("Arial"));//设置字体 

	CListBox* autoList = (CListBox*)GetDlgItem(IDC_AUTO_LIST);
	autoList->ResetContent();

	DestroyAutoCompTree();
	m_autoComp = CreateBackAutoCompleteList(stream);
	
	m_richCtrl->HideSelection(TRUE, FALSE);
	m_richCtrl->HideCaret();
	m_richCtrl->SetRedraw(FALSE);
	DWORD index = 0;

	if (bAll)
	{
		for (int i = 0; i < stream.size(); ++i)
		{
			cf.crTextColor = stream[i]._color;
			m_richCtrl->SetSel(stream[i]._begin, stream[i]._end);
			m_richCtrl->SetSelectionCharFormat(cf);
		}
	}
	else
	{
		for (int i = 0; i < stream.size(); ++i)
		{
			if (stream[i]._begin <= m_cartIndex && stream[i]._end >= m_cartIndex)
			{
				cf.crTextColor = stream[i]._color;
				m_richCtrl->SetSel(stream[i]._begin, stream[i]._end);
				m_richCtrl->SetSelectionCharFormat(cf);

				auto root = m_autoComp;
				DWORD index = 0;
				while (TRUE)
				{
					DWORD linkIndex = stream[i]._lexeme[index] - _T('\0');
					root = root->_links[linkIndex];
					if (root == NULL)
					{
						root = m_autoComp;
						autoList->ShowWindow(FALSE);
						break;
					}
					else
					{
						if (index == stream[i]._lexeme.GetLength() - 1)
						{
							m_curLexemBegin = stream[i]._begin;
							autoList->ShowWindow(TRUE);
							CPoint pt = m_richCtrl->GetCaretPos();
							CRect rc;
							m_richCtrl->GetWindowRect(rc);
							ScreenToClient(rc);
							autoList->MoveWindow(pt.x + rc.left, pt.y + rc.top + 28, 100, 100);
							break;
						}
					}
					++index;
				}

				for each(auto s in root->_words)
				{
					autoList->AddString(s);
				}

				break;
			}
		}
	}

	if (autoList->GetCount() == 0)
 		autoList->ShowWindow(FALSE);

	m_richCtrl->ShowCaret();
	m_richCtrl->HideSelection(FALSE, FALSE);
	m_richCtrl->SetRedraw(TRUE);
	m_richCtrl->RedrawWindow();
}

void recDestTree(AutoCompListNode* root)
{
	if (root == NULL)
		return;

	for (int i = 0; i < 128; ++i)
	{
		recDestTree(root->_links[i]);
	}
	delete root;
}

void CCodeNodeDlg::DestroyAutoCompTree()
{
	if (m_autoComp == NULL)
		return;

	recDestTree(m_autoComp);

	m_autoComp = NULL;
}

AutoCompListNode* CCodeNodeDlg::CreateBackAutoCompleteList(std::vector<SHLSLToken>& stream)

{
	AutoCompListNode* _root = new AutoCompListNode();
	auto root = _root;
	for (int i = 0; i < stream.size(); ++i)
	{
		if (!(stream[i]._type >= E_SYMBOL_BEGIN && stream[i]._type <= E_SYMBOL_END) &&
			stream[i]._type != E_COMMENT)
		{
			const CString& s = stream[i]._lexeme;
			DWORD index = 0;
			while (index < s.GetLength())
			{
				DWORD linkIndex = s[index] - _T('\0');
				if (root->_links[linkIndex] == NULL)
				{
					AutoCompListNode* ptr = new AutoCompListNode();
					ptr->_words.push_back(s);
					root->_links[linkIndex] = ptr;
					ptr->_c = s[index];
					root = ptr;
				}
				else
				{
					root = root->_links[linkIndex];
					if (root->_words.end() == std::find(root->_words.begin(), root->_words.end(), s))
						root->_words.push_back(s);
				}
				++index;
			}
			root = _root;
		}
	}
	return _root;
}

void CCodeNodeDlg::OnEnChangeCodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CHARRANGE rg;
	m_richCtrl = (CRichEditCtrl*)GetDlgItem(IDC_CODE_EDIT);
	m_richCtrl->GetSel(rg);
	m_cartIndex = rg.cpMin;
	m_richCtrl->GetWindowText(m_code);

	CHLSLLexer::_Lexer->m_code = _T("");

	for (int i = 0; i < m_code.GetLength(); ++i)
	{
		if (m_code[i] != _T('\r'))
			CHLSLLexer::_Lexer->m_code += m_code[i];
	}

	m_code = CHLSLLexer::_Lexer->m_code;
 	CHLSLLexer::_Lexer->LexRange(0, m_code.GetLength());

	if (m_InitDraw)
	{
		m_InitDraw = FALSE;
		ColorText(TRUE);
	}
	else
		ColorText(FALSE);

	m_richCtrl->SetSel(m_cartIndex, m_cartIndex);
}


void CCodeNodeDlg::OnBnClickedOpenCode()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog openDlg(TRUE);

	if (openDlg.DoModal() == IDOK)
	{
		m_filePath = openDlg.GetPathName();
		CEdit* filePath = (CEdit*)GetDlgItem(IDC_CODE_PATH);
		filePath->SetWindowText(m_filePath);
		m_richCtrl = (CRichEditCtrl*)GetDlgItem(IDC_CODE_EDIT);
		CStdioFile f;
		BOOL bOpen = f.Open(m_filePath, CFile::modeReadWrite);
		if (bOpen)
		{
			CString txt;
			CString tmpStr;
			while (f.ReadString(tmpStr))
			{
				txt += (tmpStr += "\n");
				tmpStr = _T("");
			}
			m_richCtrl->SetWindowText(txt);
			f.Close();
		}
	}
}


void CCodeNodeDlg::OnEnUpdateCodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}


void CCodeNodeDlg::OnEnSetfocusCodeEdit()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CCodeNodeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent != m_timer)
		return;

	CHARRANGE rg;
	m_richCtrl = (CRichEditCtrl*)GetDlgItem(IDC_CODE_EDIT);
	m_richCtrl->GetSel(rg);
	m_cartIndex = rg.cpMin;
	CStatic* lineDesc = (CStatic*)GetDlgItem(IDC_CODE_LINE);
	CString s;
	int row = 0;
	s.Format(_T(" Length: %d , Line: %d / %d , Column: %d"), m_richCtrl->GetTextLength(),
		row = m_richCtrl->LineFromChar(m_cartIndex) + 1, m_richCtrl->GetLineCount(),
		m_cartIndex- m_richCtrl->LineIndex(row-1));
	lineDesc->SetWindowText(s);
}

BOOL CCodeNodeDlg::PreTranslateMessage(MSG* pMsg)
{
	static bool down = false;
	CListBox* autoList = (CListBox*)GetDlgItem(IDC_AUTO_LIST);
	m_richCtrl = (CRichEditCtrl*)GetDlgItem(IDC_CODE_EDIT);
	if (pMsg->message == WM_KEYDOWN)
	{
		if (autoList->IsWindowVisible())
		{
			if (pMsg->wParam == VK_DOWN)
			{
				down = true;
				autoList->SetFocus();
			}
			else if (pMsg->wParam == VK_RETURN)
			{
				down ? pMsg->wParam = VK_UP : pMsg->wParam = VK_F1;
				m_richCtrl->SetFocus();
				m_richCtrl->HideSelection(TRUE, FALSE);
				m_richCtrl->HideCaret();
				m_richCtrl->SetRedraw(FALSE);

				CString s;
				autoList->GetText(autoList->GetCurSel(), s);
				m_richCtrl->SetSel(m_curLexemBegin, m_cartIndex - 1);
				m_richCtrl->ReplaceSel(s);

				m_richCtrl->ShowCaret();
				m_richCtrl->HideSelection(FALSE, FALSE);
				m_richCtrl->SetRedraw(TRUE);
				m_richCtrl->RedrawWindow();

				autoList->ShowWindow(FALSE);

				down = false;
			}
			else if (pMsg->wParam == VK_ESCAPE)
			{
				down ? pMsg->wParam = VK_UP : pMsg->wParam = VK_F1;
				m_richCtrl->SetFocus();
				autoList->ShowWindow(FALSE);
				m_richCtrl->SetSel(m_cartIndex, m_cartIndex);

				down = false;
			}
			else
				down = false;
		}	
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}