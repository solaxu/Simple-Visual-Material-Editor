// InoutputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "InoutputDlg.h"
#include "afxdialogex.h"
#include "UI.h"


// CInoutputDlg 对话框

IMPLEMENT_DYNAMIC(CInoutputDlg, CDialogEx)

CInoutputDlg::CInoutputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INOUT_DLG, pParent)
{

}

CInoutputDlg::~CInoutputDlg()
{
}

void CInoutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInoutputDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInoutputDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CInoutputDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CInoutputDlg::OnBnClickedButtonSub)
END_MESSAGE_MAP()

BOOL CInoutputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetAllCtrls();

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_types[i]->AddString(ShaderEditor::FloatTypes[j]);
		}

		for (int j = 0; j < 34; ++j)
		{
			m_semantics[i]->AddString(ShaderEditor::Semantics[j]);
		}
	}

	for (int i = 0; i < m_count; ++i)
	{
		m_names[i]->ShowWindow(SW_SHOW);
		m_types[i]->ShowWindow(SW_SHOW);
		m_semantics[i]->ShowWindow(SW_SHOW);

		m_types[i]->SetCurSel(0);
		m_semantics[i]->SetCurSel(0);

		m_names[i]->SetWindowText(M_NAMES[i]);

		for (int j = 0; j < 4; ++j)
		{
			if (ShaderEditor::FloatTypes[j] == M_TYPES[i])
			{
				m_types[i]->SetCurSel(j);
				break;
			}
		}

		for (int j = 0; j < 34; ++j)
		{
			if (ShaderEditor::Semantics[j] == M_SEMANTICS[i])
			{
				m_semantics[i]->SetCurSel(j);
				break;
			}
		}
	}

	return 1;
}

void CInoutputDlg::GetAllCtrls()
{
	m_names.clear();
	m_types.clear();
	m_semantics.clear();

	CEdit* name = NULL;
	CComboBox* semantic = NULL;
	CComboBox* type = NULL;

	name = (CEdit*)GetDlgItem(IDC_EDIT1); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT2); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT3); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT4); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT5); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT6); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT7); name->ShowWindow(SW_HIDE);	m_names.push_back(name);
	name = (CEdit*)GetDlgItem(IDC_EDIT8); name->ShowWindow(SW_HIDE);	m_names.push_back(name);

	type = (CComboBox*)GetDlgItem(IDC_COMBO1); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO3); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO5); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO7); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO9); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO11); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO13); type->ShowWindow(SW_HIDE); m_types.push_back(type);
	type = (CComboBox*)GetDlgItem(IDC_COMBO15); type->ShowWindow(SW_HIDE); m_types.push_back(type);

	semantic = (CComboBox*)GetDlgItem(IDC_COMBO2); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO4); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO6); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO8); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO10); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO12); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO14); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
	semantic = (CComboBox*)GetDlgItem(IDC_COMBO16); semantic->ShowWindow(SW_HIDE); m_semantics.push_back(semantic);
}

// CInoutputDlg 消息处理程序


void CInoutputDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	M_NAMES.clear();
	M_TYPES.clear();
	M_SEMANTICS.clear();

	GetAllCtrls();

	for (int i = 0; i < m_count; ++i)
	{
		CString s;
		m_names[i]->GetWindowText(s);
		M_NAMES.push_back(s);

		m_types[i]->GetLBText(m_types[i]->GetCurSel(), s);
		M_TYPES.push_back(s);

		m_semantics[i]->GetLBText(m_semantics[i]->GetCurSel(), s);
		M_SEMANTICS.push_back(s);
	}
}


void CInoutputDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码

//	GetAllCtrls();

	++m_count;

	if (m_count > 8)
	{
		--m_count;
		MessageBox(_T("Maxmized count is 8"), _T("Warning"));
		return;
	}

	m_names[m_count - 1]->ShowWindow(SW_SHOW);
	m_types[m_count - 1]->ShowWindow(SW_SHOW);
	m_semantics[m_count - 1]->ShowWindow(SW_SHOW);
	m_types[m_count - 1]->SetCurSel(0);
	m_semantics[m_count - 1]->SetCurSel(0);
}


void CInoutputDlg::OnBnClickedButtonSub()
{
	// TODO: 在此添加控件通知处理程序代码

	--m_count;

	if (m_count < 0)
	{
		++m_count;
		MessageBox(_T("Minmized count is 0"), _T("Warning"));
		return;
	}

	m_names[m_count]->ShowWindow(SW_HIDE);
	m_types[m_count]->ShowWindow(SW_HIDE);
	m_semantics[m_count]->ShowWindow(SW_HIDE);
}
