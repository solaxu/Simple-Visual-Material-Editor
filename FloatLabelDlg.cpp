// FloatLabelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "FloatLabelDlg.h"
#include "afxdialogex.h"
#include <string>


// CFloatLabelDlg �Ի���

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


// CFloatLabelDlg ��Ϣ�������

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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CFloatLabelDlg::OnNMCustomdrawFltSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(IDC_FLT_SLIDER);
	value = slider->GetPos();
	CString v;
	v.Format(_T("%3.2f"), value);
	CEdit* VEdit = (CEdit*)GetDlgItem(IDC_FLT_VALUE);
	VEdit->SetWindowText(v);
}
