
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "D3D9DockWnd.h"
#include "PropertyDockWnd.h"
#include "ResourceMgrWnd.h"
#include "ToolBoxWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

public:
	CD3D9DockWnd m_previewWnd;
	CPropertyDockWnd m_propertyWnd;
	CResourceMgrWnd m_resMgrWnd;
	// CToolBoxWnd m_toolbocWnd;
protected:
	BOOL AddDockWindow(DWORD style, CDockablePane& dockWnd, CString& title, DWORD id, CWnd* parent);
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCompileRun();
};


