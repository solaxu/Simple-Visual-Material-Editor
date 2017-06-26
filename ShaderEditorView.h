
// ShaderEditorView.h : interface of the CShaderEditorView class
//

#pragma once
#include <afxcmn.h>
#include <afxcview.h>
#include "D3DView.h"
#include "ShaderEditorDoc.h"


class CShaderEditorView : public CTabView
{

public:
	static CD3DView* VSH_Canvas;
	static CD3DView* PSH_Canvas;

protected: // create from serialization only
	CShaderEditorView();
	DECLARE_DYNCREATE(CShaderEditorView)

// Attributes
public:
	CShaderEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CShaderEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCompileRun();
};

#ifndef _DEBUG  // debug version in ShaderEditorView.cpp
inline CShaderEditorDoc* CShaderEditorView::GetDocument() const
   { return reinterpret_cast<CShaderEditorDoc*>(m_pDocument); }
#endif

