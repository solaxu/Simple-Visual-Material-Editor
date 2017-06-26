// SamplerTexDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "SamplerTexDlg.h"
#include "afxdialogex.h"
#include "UI.h"
#include <string>


// CSamplerTexDlg 对话框

IMPLEMENT_DYNAMIC(CSamplerTexDlg, CDialogEx)

CSamplerTexDlg::CSamplerTexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SAMPLER_DLG, pParent),
	AddrU(0),AddrV(0),AddrW(0),FilterMip(0),FilterMin(0),FilterMag(0),
	MaxMipLvl(0),BorderR(0),BorderB(0),BorderG(0),BorderA(0)
{

}

CSamplerTexDlg::~CSamplerTexDlg()
{
}

void CSamplerTexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSamplerTexDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAMPLER_TEX_SELECTOR, &CSamplerTexDlg::OnBnClickedSamplerTexSelector)
	ON_BN_CLICKED(IDOK, &CSamplerTexDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSamplerTexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComboBox* addrU = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRU);
	CComboBox* addrV = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRV);
	CComboBox* addrW = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRW);
	CComboBox* filterMag = (CComboBox*)GetDlgItem(IDC_SAMPLER_MAGFILTER);
	CComboBox* filterMin = (CComboBox*)GetDlgItem(IDC_SAMPLER_MINFILTER);
	CComboBox* filterMip = (CComboBox*)GetDlgItem(IDC_SAMPLER_MIPFILTER);
	CComboBox* maxmipLvl = (CComboBox*)GetDlgItem(IDC_SAMPLER_MAXMIPLVL);

	CEdit* bR = (CEdit*)GetDlgItem(IDC_BORDER_R);
	CEdit* bG = (CEdit*)GetDlgItem(IDC_BORDER_G);
	CEdit* bB = (CEdit*)GetDlgItem(IDC_BORDER_B);
	CEdit* bA = (CEdit*)GetDlgItem(IDC_BORDER_A);

	CEdit* texPath = (CEdit*)GetDlgItem(IDC_SAMPLER_TEX_PATH);

	for (auto str : ShaderEditor::TextureAddress)
	{
		addrU->AddString(str);
		addrV->AddString(str);
		addrW->AddString(str);
	}

	for (auto str : ShaderEditor::TexturerMagFilter)
	{
		filterMip->AddString(str);
		filterMag->AddString(str);
		filterMin->AddString(str);
	}

	for (auto str : ShaderEditor::TextureMaxMipLevel)
	{
		maxmipLvl->AddString(str);
	}

	addrU->SetCurSel(AddrU);
	addrV->SetCurSel(AddrV);
	addrW->SetCurSel(AddrW);

	filterMag->SetCurSel(FilterMag);
	filterMin->SetCurSel(FilterMin);
	filterMip->SetCurSel(FilterMip);

	maxmipLvl->SetCurSel(MaxMipLvl);

	texPath->SetWindowText(TexPath);

	CString s;
	s.Format(_T("%d"), BorderR);
	bR->SetWindowText(s);
	s = _T("");

	s.Format(_T("%d"), BorderG);
	bG->SetWindowText(s);
	s = _T("");

	s.Format(_T("%d"), BorderB);
	bB->SetWindowText(s);
	s = _T("");

	s.Format(_T("%d"), BorderA);
	bA->SetWindowText(s);

	return 1;
}

// CSamplerTexDlg 消息处理程序


void CSamplerTexDlg::OnBnClickedSamplerTexSelector()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog openDlg(TRUE);

	if (openDlg.DoModal() == IDOK)
	{
		TexPath = openDlg.GetPathName();
		CEdit* texPath = (CEdit*)GetDlgItem(IDC_SAMPLER_TEX_PATH);
		texPath->SetWindowText(TexPath);
	}
}


void CSamplerTexDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	CComboBox* addrU = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRU);
	CComboBox* addrV = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRV);
	CComboBox* addrW = (CComboBox*)GetDlgItem(IDC_SAMPLER_ADDRW);
	CComboBox* filterMag = (CComboBox*)GetDlgItem(IDC_SAMPLER_MAGFILTER);
	CComboBox* filterMin = (CComboBox*)GetDlgItem(IDC_SAMPLER_MINFILTER);
	CComboBox* filterMip = (CComboBox*)GetDlgItem(IDC_SAMPLER_MIPFILTER);
	CComboBox* maxmipLvl = (CComboBox*)GetDlgItem(IDC_SAMPLER_MAXMIPLVL);

	CEdit* bR = (CEdit*)GetDlgItem(IDC_BORDER_R);
	CEdit* bG = (CEdit*)GetDlgItem(IDC_BORDER_G);
	CEdit* bB = (CEdit*)GetDlgItem(IDC_BORDER_B);
	CEdit* bA = (CEdit*)GetDlgItem(IDC_BORDER_A);

	CEdit* texPath = (CEdit*)GetDlgItem(IDC_SAMPLER_TEX_PATH);

	AddrU = addrU->GetCurSel();
	AddrV = addrV->GetCurSel();
	AddrW = addrW->GetCurSel();

	FilterMag = filterMag->GetCurSel();
	FilterMin = filterMin->GetCurSel();
	FilterMip = filterMip->GetCurSel();

	MaxMipLvl = maxmipLvl->GetCurSel();

	CString cstr;

	bA->GetWindowText(cstr);
	BorderA = _ttol(cstr);

	bR->GetWindowText(cstr);
	BorderR = _ttol(cstr);

	bG->GetWindowText(cstr);
	BorderG = _ttol(cstr);

	bB->GetWindowText(cstr);
	BorderB = _ttol(cstr);

	texPath->GetWindowText(TexPath);
}
