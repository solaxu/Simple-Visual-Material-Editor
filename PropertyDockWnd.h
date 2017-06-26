#pragma once


// CPropertyDockWnd

#include "RenderSatateDlg.h"
class CPropertyDockWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CPropertyDockWnd)

public:
	CPropertyDockWnd();
	virtual ~CPropertyDockWnd();

public:
	CRenderSatateDlg dlg;
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


