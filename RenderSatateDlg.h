#pragma once

#include "UI.h"
#include "UIMgr.h"

// CRenderSatateDlg �Ի���

class CRenderSatateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderSatateDlg)

public:
	CRenderSatateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRenderSatateDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDERSTATE_DLG };
#endif

	virtual BOOL OnInitDialog();

	CListCtrl* m_listCtrl;
	ShaderEditor::SRenderState _RenderState;

public:



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat);
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem);

	bool createCEdit = false;
	bool createCCombox = false;
	CEdit _ptrEdit;
	CComboBox _ptrCombox;
	int _item = 0;
	int _subItem = 0;

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnHdnTrackRstateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnHotTrackRstateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnBegintrackRstateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnEndtrackRstateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickRstateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEdit();//��̬���ɱ༭��ʧȥ������Ӧ����
	afx_msg void OnKillfocusCcomboBox();//��̬���������б��ʧȥ������Ӧ����
	afx_msg void OnNMKillfocusRstateList(NMHDR *pNMHDR, LRESULT *pResult);
};
