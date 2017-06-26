// LabelEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "LabelEditDlg.h"
#include "afxdialogex.h"


// CLabelEditDlg 对话框

IMPLEMENT_DYNAMIC(CLabelEditDlg, CDialogEx)

CLabelEditDlg::CLabelEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LABEL_EDIT, pParent)
{

}

CLabelEditDlg::~CLabelEditDlg()
{
}

void CLabelEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLabelEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLabelEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLabelEditDlg 消息处理程序

BOOL CLabelEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_LABEL);
	edit->SetWindowText(text);
	return 1;
}


void CLabelEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_LABEL);
	edit->GetWindowText(text);
}
