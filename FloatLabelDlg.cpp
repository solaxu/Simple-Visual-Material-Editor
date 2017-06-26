// FloatLabelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "FloatLabelDlg.h"
#include "afxdialogex.h"
#include <string>


// CFloatLabelDlg 对话框

IMPLEMENT_DYNAMIC(CFloatLabelDlg, CDialogEx)

CFloatLabelDlg::CFloatLabelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FLOAT_VALUE, pParent), value(0.0f), M_MAX(100.0f), M_MIN(0.0f)
{

}

CFloatLabelDlg::~CFloatLabelDlg()
{
}

void CFloatLabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFloatLabelDlg, CDialogEx)
	ON_EN_CHANGE(IDC_FLT_MIN, &CFloatLabelDlg::OnEnChangeFltMin)
	ON_EN_CHANGE(IDC_FLT_MAX, &CFloatLabelDlg::OnEnChangeFltMax)
	ON_BN_CLICKED(IDOK, &CFloatLabelDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FLT_SLIDER, &CFloatLabelDlg::OnNMCustomdrawFltSlider)
END_MESSAGE_MAP()


// CFloatLabelDlg 消息处理程序

BOOL CFloatLabelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString v;
	v.Format(_T("%3.2f"), value);
	CEdit* minEdit = (CEdit*)GetDlgItem(IDC_FLT_MIN);
	CEdit* maxEdit = (CEdit*)GetDlgItem(IDC_FLT_MAX);

	CEdit* vEdit = (CEdit*)GetDlgItem(IDC_FLT_VALUE);
	vEdit->SetWindowText(v);
	v = _T("");
	v.Format(_T("%3.2f"), M_MIN);
	minEdit->SetWindowText(v);

	v = _T("");
	v.Format(_T("%3.2f"), M_MAX);
	maxEdit->SetWindowTextW(v);

	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_FLT_SLIDER);
	slider->SetRange(M_MIN, M_MAX, TRUE);
	slider->SetPos(value);

	return 1;
}

void CFloatLabelDlg::OnEnChangeFltMin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString minV;
	CEdit* edit = (CEdit*)GetDlgItem(IDC_FLT_MIN);
	edit->GetWindowText(minV);
	if (minV == _T("-"))
		return;
	M_MIN = std::stof(minV.GetString());
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_FLT_SLIDER);
	slider->SetRange(M_MIN, M_MAX, TRUE);
}


void CFloatLabelDlg::OnEnChangeFltMax()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString maxV;
	CEdit* edit = (CEdit*)GetDlgItem(IDC_FLT_MAX);
	edit->GetWindowText(maxV);
	if (maxV == _T("-"))
		return;
	M_MAX = std::stof(maxV.GetString());
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_FLT_SLIDER);
	slider->SetRange(M_MIN, M_MAX, TRUE);
}


void CFloatLabelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CFloatLabelDlg::OnNMCustomdrawFltSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_FLT_SLIDER);
	value = slider->GetPos();
	CString v;
	v.Format(_T("%3.2f"), value);
	CEdit* VEdit = (CEdit*)GetDlgItem(IDC_FLT_VALUE);
	VEdit->SetWindowText(v);
}
