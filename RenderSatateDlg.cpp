// RenderSatateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "RenderSatateDlg.h"
#include "afxdialogex.h"


// CRenderSatateDlg �Ի���

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

// CRenderSatateDlg ��Ϣ�������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}


void CRenderSatateDlg::OnLvnHotTrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}


void CRenderSatateDlg::OnHdnBegintrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}


void CRenderSatateDlg::OnHdnEndtrackRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}


void CRenderSatateDlg::OnNMClickRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
#ifdef DEBUG
	CString test;
	test.Format(_T("�У�%d���У�%d\n"), pEditCtrl->iItem, pEditCtrl->iSubItem);
#endif

	if (createCEdit == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//���ٵ�Ԫ��༭�����
		createCEdit = false;
	}
	if (createCCombox == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}

	if (pEditCtrl->iSubItem == 1)//������ǹ�����
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
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_CREATE_EDIT);//�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��3000�������¿�ͷ����
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createdit->SetParent(m_listCtrl);//��list control����Ϊ������,���ɵ�Edit������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_listCtrl->GetSubItemRect(_item, _subItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listCtrl->GetColumnWidth(_subItem) - 1, EditRect.bottom - 1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_listCtrl->GetItemText(_item, _subItem);//�����Ӧ��Ԫ���ַ�
	createdit->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createdit->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createdit->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
	createdit->SetFocus();//����Ϊ���� 
	createdit->SetSel(-1);//���ù�����ı������ֵ����
}

void CRenderSatateDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//�����Ӧ��Ԫ���ַ�
	distroyedit->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
	createCEdit = false;
	Invalidate();
}

void CRenderSatateDlg::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), this, IDC_CREATE_COMBOX);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createccomboboxobj->SetParent(m_listCtrl);//��list control����Ϊ������,���ɵ�Ccombobox������ȷ��λ,���Ҳ����Ҫ
	createccomboboxobj->SetMinVisibleItems(5);
	CRect  EditRect;
	m_listCtrl->GetSubItemRect(_item, _subItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_listCtrl->GetColumnWidth(_subItem) - 1, EditRect.bottom + 50);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_listCtrl->GetItemText(_item, _subItem);//�����Ӧ��Ԫ���ַ�
	createccomboboxobj->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createccomboboxobj->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createccomboboxobj->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
}

void CRenderSatateDlg::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//������Ӧ��Ԫ���ַ�
	distroyccomboboxobj->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
	createCCombox = false;
	Invalidate();
}

void CRenderSatateDlg::OnKillfocusEdit()
{
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	if (createCEdit == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//���ٵ�Ԫ��༭�����
		createCEdit = false;
	}
	if (createCCombox == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}
}

void CRenderSatateDlg::OnKillfocusCcomboBox()
{
	m_listCtrl = (CListCtrl*)GetDlgItem(IDC_RSTATE_LIST);
	if (createCEdit == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(m_listCtrl, &_ptrEdit, _item, _subItem);//���ٵ�Ԫ��༭�����
		createCEdit = false;
	}
	if (createCCombox == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(m_listCtrl, &_ptrCombox, _item, _subItem);
		createCCombox = false;
	}
}

void CRenderSatateDlg::OnNMKillfocusRstateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
