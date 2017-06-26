// RenderSatateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "RenderSatateDlg.h"
#include "afxdialogex.h"


// CRenderSatateDlg 对话框

IMPLEMENT_DYNAMIC(CRenderSatateDlg, CDialogEx)

#define IDC_CREATE_EDIT 2020
#define IDC_CREATE_COMBOX 2021

CRenderSatateDlg::CRenderSatateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CRenderSatateDlg::~CRenderSatateDlg()
{
}

void CRenderSatateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRenderSatateDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(HDN_TRACK, 0, &CRenderSatateDlg::OnHdnTrackRstateList)
	ON_NOTIFY(LVN_HOTTRACK, IDC_RSTATE_LIST, &CRenderSatateDlg::OnLvnHotTrackRstateList)
	ON_NOTIFY(HDN_BEGINTRACK, 0, &CRenderSatateDlg::OnHdnBegintrackRstateList)
	ON_NOTIFY(HDN_ENDTRACK, 0, &CRenderSatateDlg::OnHdnEndtrackRstateList)
	ON_NOTIFY(NM_CLICK, IDC_RSTATE_LIST, &CRenderSatateDlg::OnNMClickRstateList)
	ON_EN_KILLFOCUS(IDC_CREATE_EDIT, &CRenderSatateDlg::OnKillfocusEdit)
	ON_CBN_KILLFOCUS(IDC_CREATE_COMBOX, &CRenderSatateDlg::OnKillfocusCcomboBox)
	ON_NOTIFY(NM_KILLFOCUS, IDC_RSTATE_LIST, &CRenderSatateDlg::OnNMKillfocusRstateList)
END_MESSAGE_MAP()

BOOL CRenderSatateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);

	CRect rc;
	GetClientRect(rc);
	m_listCtrl->MoveWindow(&rc);
	RECT  rect;
	m_listCtrl->GetClientRect(&rect);
	m_listCtrl->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	m_listCtrl->InsertColumn(0, _T("Render State"), LVCFMT_LEFT, rect.right/2);
	m_listCtrl->InsertColumn(1, _T("Value"), LVCFMT_LEFT, rect.right / 2);

	//
	m_listCtrl->InsertItem(0, _T("Alpha blend enable"));
	m_listCtrl->SetItemText(0, 1, _RenderState._AlphaBlendEnable);

	m_listCtrl->InsertItem(1, _T("Alpha function"));
	m_listCtrl->SetItemText(1, 1, _RenderState._AlphaFunc);

	m_listCtrl->InsertItem(2, _T("Alpha ref"));
	m_listCtrl->SetItemText(2, 1, _RenderState._AlphaRef);

	m_listCtrl->InsertItem(3, _T("Alpha test enable"));
	m_listCtrl->SetItemText(3, 1, _RenderState._AlphaTestEnalbe);

	m_listCtrl->InsertItem(4, _T("Blend operation"));
	m_listCtrl->SetItemText(4, 1, _RenderState._BlendOp);

	m_listCtrl->InsertItem(5, _T("Dest blend"));
	m_listCtrl->SetItemText(5, 1, _RenderState._DestBlend);

	m_listCtrl->InsertItem(6, _T("Fill mode"));
	m_listCtrl->SetItemText(6, 1, _RenderState._FillMode);

	m_listCtrl->InsertItem(7, _T("Shade mode"));
	m_listCtrl->SetItemText(7, 1, _RenderState._ShadeMode);

	m_listCtrl->InsertItem(8, _T("Source blend"));
	m_listCtrl->SetItemText(8, 1, _RenderState._SrcBlend);

	m_listCtrl->InsertItem(9, _T("Z buffer Enable"));
	m_listCtrl->SetItemText(9, 1, _RenderState._ZEnable);

	m_listCtrl->InsertItem(10, _T("Z buffer function"));
	m_listCtrl->SetItemText(10, 1, _RenderState._ZFunc);

	m_listCtrl->InsertItem(11, _T("Z buffer wirte enable"));
	m_listCtrl->SetItemText(11, 1, _RenderState._ZWritEnable);

	m_listCtrl->InsertItem(12, _T("VSH Compile Version"));
	m_listCtrl->SetItemText(12, 1, _RenderState._AlphaBlendEnable);

	m_listCtrl->InsertItem(13, _T("PSH Compile Version"));
	m_listCtrl->SetItemText(13, 1, _RenderState._AlphaBlendEnable);


	m_listCtrl->GetHeaderCtrl()->EnableWindow(FALSE);
	return TRUE;
}

BOOL CRenderSatateDlg::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CDialogEx::OnChildNotify(message, wParam, lParam, pResult);
}

// CRenderSatateDlg 消息处理程序

void CRenderSatateDlg::OnSize(UINT nType, int cx, int cy)
{
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	if (m_listCtrl)
	{
		CRect rc;
		GetClientRect(rc);
		m_listCtrl->MoveWindow(&rc);
		m_listCtrl->GetClientRect(rc);
		m_listCtrl->SetColumnWidth(0,rc.Width() / 2);
		m_listCtrl->SetColumnWidth(1,rc.Width() / 2);
	}
}

void CRenderSatateDlg::OnHdnTrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 1;
}


void CRenderSatateDlg::OnLvnHotTrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 1;
}


void CRenderSatateDlg::OnHdnBegintrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 1;
}


void CRenderSatateDlg::OnHdnEndtrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 1;
}


void CRenderSatateDlg::OnNMClickRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
#ifdef DEBUG
	CString test;
	test.Format(_T("行：%d，列：%d\n"), pEditCtrl->iItem, pEditCtrl->iSubItem);
#endif

	if (createCEdit == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//销毁单元格编辑框对象
		createCEdit = false;
	}
	if (createCCombox == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}

	if (pEditCtrl->iSubItem == 1)//点击到非工作区
	{
		switch (pEditCtrl->iItem)
		{
		case 0: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			_ptrCombox.AddString(_T("True"));
			_ptrCombox.AddString(_T("False"));
			_ptrCombox.ShowDropDown();
		}break;
		case 1: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::AlphaFuncStr)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		case 2: {
			createEdit(pEditCtrl, &_ptrEdit, _item, _subItem, createCEdit);
		}break;
		case 3: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			_ptrCombox.AddString(_T("True"));
			_ptrCombox.AddString(_T("False"));
			_ptrCombox.ShowDropDown(); 
		}break;
		case 4: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::BlendOpStr)
			{
				_ptrCombox.AddString(s);
			}
			auto i = _ptrCombox.GetCount();
			_ptrCombox.ShowDropDown();
		}break;
		case 5: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::DestBlend)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown();
		}break;
		case 6: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::FillModeStr)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		case 7: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::ShadeMode)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		case 8: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::SrcBlendStr)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		case 9: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			_ptrCombox.AddString(_T("True"));
			_ptrCombox.AddString(_T("False"));
			_ptrCombox.ShowDropDown(); 
		}break;
		case 10: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::AlphaFuncStr)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		case 11: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			_ptrCombox.AddString(_T("True"));
			_ptrCombox.AddString(_T("False"));
			_ptrCombox.ShowDropDown(); 
		}break;
		case 12: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::VSHVersion)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown();
		}break;
		case 13: {
			createCcombobox(pEditCtrl, &_ptrCombox, _item, _subItem, createCCombox);
			for each(CString s in ShaderEditor::PSHVersion)
			{
				_ptrCombox.AddString(s);
			}
			_ptrCombox.ShowDropDown(); 
		}break;
		}
	}
}

void CRenderSatateDlg::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_CREATE_EDIT);//创建编辑框对象,IDC_EDIT_CREATEID为控件ID号3000，在文章开头定义
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createdit->SetParent(m_listCtrl);//将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要
	CRect  EditRect;
	m_listCtrl->GetSubItemRect(_item, _subItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listCtrl->GetColumnWidth(_subItem) - 1, EditRect.bottom - 1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_listCtrl->GetItemText(_item, _subItem);//获得相应单元格字符
	createdit->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createdit->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createdit->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
	createdit->SetFocus();//设置为焦点 
	createdit->SetSel(-1);//设置光标在文本框文字的最后
}

void CRenderSatateDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//获得相应单元格字符
	distroyedit->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
	createCEdit = false;
	Invalidate();
}

void CRenderSatateDlg::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), this, IDC_CREATE_COMBOX);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createccomboboxobj->SetParent(m_listCtrl);//将list control设置为父窗口,生成的Ccombobox才能正确定位,这个也很重要
	createccomboboxobj->SetMinVisibleItems(5);
	CRect  EditRect;
	m_listCtrl->GetSubItemRect(_item, _subItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listCtrl->GetColumnWidth(_subItem) - 1, EditRect.bottom + 50);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_listCtrl->GetItemText(_item, _subItem);//获得相应单元格字符
	createccomboboxobj->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createccomboboxobj->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createccomboboxobj->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
}

void CRenderSatateDlg::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//更新相应单元格字符
	distroyccomboboxobj->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
	createCCombox = false;
	Invalidate();
}

void CRenderSatateDlg::OnKillfocusEdit()
{
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	if (createCEdit == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//销毁单元格编辑框对象
		createCEdit = false;
	}
	if (createCCombox == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}
}

void CRenderSatateDlg::OnKillfocusCcomboBox()
{
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	if (createCEdit == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//销毁单元格编辑框对象
		createCEdit = false;
	}
	if (createCCombox == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}
}

void CRenderSatateDlg::OnNMKillfocusRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	
	_RenderState._AlphaBlendEnable = m_listCtrl->GetItemText(0, 1);
	_RenderState._AlphaFunc = m_listCtrl->GetItemText(1, 1);
	_RenderState._AlphaRef = m_listCtrl->GetItemText(2, 1);
	_RenderState._AlphaTestEnalbe = m_listCtrl->GetItemText(3, 1);
	_RenderState._BlendOp = m_listCtrl->GetItemText(4, 1);
	_RenderState._DestBlend = m_listCtrl->GetItemText(5, 1);
	_RenderState._FillMode = m_listCtrl->GetItemText(6, 1);
	_RenderState._ShadeMode = m_listCtrl->GetItemText(7, 1);
	_RenderState._SrcBlend = m_listCtrl->GetItemText(8, 1);
	_RenderState._ZEnable = m_listCtrl->GetItemText(9, 1);
	_RenderState._ZFunc = m_listCtrl->GetItemText(10, 1);
	_RenderState._ZWritEnable = m_listCtrl->GetItemText(11, 1);
	_RenderState._vshVersion = m_listCtrl->GetItemText(12, 1);
	_RenderState._pshVersion = m_listCtrl->GetItemText(13, 1);
}
