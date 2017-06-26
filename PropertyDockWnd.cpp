// PropertyDockWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "PropertyDockWnd.h"
#include "MainFrm.h"


// CPropertyDockWnd

IMPLEMENT_DYNAMIC(CPropertyDockWnd, CDockablePane)

CPropertyDockWnd::CPropertyDockWnd()
{

}

CPropertyDockWnd::~CPropertyDockWnd()
{
}


BEGIN_MESSAGE_MAP(CPropertyDockWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPropertyDockWnd ��Ϣ�������

int CPropertyDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CDockablePane::OnCreate(lpCreateStruct);

	CRect rc;
	
	GetClientRect(rc);

	dlg.Create(IDD_RENDERSTATE_DLG, this);
	dlg.MoveWindow(rc);
	dlg.ShowWindow(SW_SHOW);

	return 1;
}

void CPropertyDockWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	GetClientRect(&rc);
	dlg.MoveWindow(rc);
}