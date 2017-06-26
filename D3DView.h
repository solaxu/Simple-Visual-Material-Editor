#pragma once

#include "Ulit.h"

#include "UI.h"
#include "UIMgr.h"

// CD3DView 视图

class CD3DView : public CView
{
	DECLARE_DYNCREATE(CD3DView)

protected:
	CD3DView();           // 动态创建所使用的受保护的构造函数
	virtual ~CD3DView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	LPDIRECT3D9 m_d3d9 = NULL;
	LPDIRECT3DDEVICE9 m_d3d9Device = NULL;
	LPD3DXFONT m_font;
	ShaderEditor::UIMgr m_uis;
	DWORD m_shType;
	CString m_Code;
protected:
	UINT m_timerIndex = 1;
	ShaderEditor::SUIButton* m_linkBtnCur = NULL; // 当前被选中的按钮
	ShaderEditor::SUIWindow* m_wndCur = NULL; // 当前选中的窗口
	float m_curMouseX = 0.0f;
	float m_curMouseY = 0.0f;
	ShaderEditor::SUIButton* M_LINKBTN = NULL;
public:
	// 重载
	virtual void Draw();
	virtual BOOL InitDirect9();

protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDisconnect();
	afx_msg void OnMatrixWorldmatrix32906();
	afx_msg void OnMatrixViewmatrix();
	afx_msg void OnMatrixProjectmatrix();
	afx_msg void OnMatrixInverseworldmatrix();
	afx_msg void OnMatrixInverseviewmatrix();
	afx_msg void OnMatrixInverseprojectmatrix();
	afx_msg void OnMatrixWorldviewmatrix();
	afx_msg void OnMatrixWorldviewprojectmatrix();
	afx_msg void OnMatrixInverseworldviewmatrix();
	afx_msg void OnMatrixInverseworldviewprojectmatrix32907();
	afx_msg void OnMatrixTranspose();
	afx_msg void OnVectorFloat();
	afx_msg void OnVectorFloat2();
	afx_msg void OnVectorFloat3();
	afx_msg void OnVectorFloat5();
	afx_msg void OnSamplerSampler2d();
	afx_msg void OnVectoroperationsAppend32902();
	afx_msg void OnVectoroperationsCrossproduct();
	afx_msg void OnVectoroperationsDotproduct();
	afx_msg void OnVectoroperationsDistance();
	afx_msg void OnVectoroperationsLength();
	afx_msg void OnVectoroperationsNormalize();
	afx_msg void OnVectoroperationsReflect();
	afx_msg void OnVectoroperationsRefract();
	afx_msg void OnVectoroperationsTransform32909();
	afx_msg void OnMathematicalfunctionsArcsin();
	afx_msg void OnMathematicalfunctionsArccos();
	afx_msg void OnMathematicalfunctionsArctan();
	afx_msg void OnMathematicalfunctionsAdd();
	afx_msg void OnMathematicalfunctionsAbs();
	afx_msg void OnMathematicalfunctionsCeil();
	afx_msg void OnMathematicalfunctionsClamp();
	afx_msg void OnMathematicalfunctionsCos();
	afx_msg void OnMathematicalfunctionsDdx();
	afx_msg void OnMathematicalfunctionsDdy();
	afx_msg void OnMathematicalfunctionsDegree32848();
	afx_msg void OnMathematicalfunctionsDiv();
	afx_msg void OnExpExpe();
	afx_msg void OnExpExp3();
	afx_msg void OnMathematicalfunctionsMod();
	afx_msg void OnMathematicalfunctionsFloor();
	afx_msg void OnMathematicalfunctionsLit();
	afx_msg void OnMathematicalfunctionsLerp();
	afx_msg void OnLogExp2();
	afx_msg void OnLogLog2();
	afx_msg void OnLogLog11();
	afx_msg void OnMathematicalfunctionsMax32847();
	afx_msg void OnMathematicalfunctionsMin();
	afx_msg void OnMathematicalfunctionsMul();
	afx_msg void OnMathematicalfunctionsNoise();
	afx_msg void OnMathematicalfunctionsPower32846();
	afx_msg void OnMathematicalfunctionsReciprocal();
	afx_msg void OnMathematicalfunctionsRound();
	afx_msg void OnMathematicalfunctionsRadian();
	afx_msg void OnMathematicalfunctionsSin();
	afx_msg void OnMathematicalfunctionsSqrt();
	afx_msg void OnMathematicalfunctionsSaturate32854();
	afx_msg void OnMathematicalfunctionsSubtract();
	afx_msg void OnMathematicalfunctionsTan();
	afx_msg void OnEditDelNode();
	afx_msg void OnAddnodeInputnode32912();
	afx_msg void OnAddnodeOutputnode32913();
	afx_msg void OnAddnodeCodenode();
	afx_msg void OnSingleViewRun();
};


