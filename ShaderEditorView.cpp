
// ShaderEditorView.cpp : implementation of the CShaderEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ShaderEditor.h"
#endif

#include "ShaderEditorDoc.h"
#include "ShaderEditorView.h"

#include "UIMaterialNodeAppend.h"
#include "UIMaterialNodeWorldMatrix.h"
#include "UIMaterialNodeViewMatrix.h"
#include "UIMaterialNodeProjectMat.h"
#include "UIMaterialNodeWorldViewMatrix.h"
#include "UIMaterialNodeWorldViewProjMatrix.h"
#include "UIMaterialNodeInvWorldMatrix.h"
#include "UIMaterialNodeInvView.h"
#include "UIMaterialNodeInvProjMatrix.h"
#include "UIMaterialNodeInvWOrldViewMatrix.h"
#include "UIMaterialNodeInvWorldViewProjMatrix.h"
#include "UIMaterialNodeMatTranspose.h"
#include "UIMaterialNodeFloat.h"
#include "UIMaterialNodeFloat2.h"
#include "UIMaterialNodeFloat3.h"
#include "UIMaterialNodeFloat4.h"
#include "UIMaterialNodeSampler2D.h"
#include "UIMaterialNodeCross.h"
#include "UIMaterialNodeDot.h"
#include "UIMaterialNodeLength.h"
#include "UIMaterialNodeNormalize.h"
#include "UIMaterialNodeReflect.h"
#include "UIMaterialNodeDistance.h"
#include "UIMaterialNodeRefract.h"
#include "UIMaterialNodeTransofrm.h"
#include "UIMaterialNodeArcsin.h"
#include "UIMaterialNodeArccos.h"
#include "UIMaterialNodeArctan.h"
#include "UIMaterialNodeSin.h"
#include "UIMaterialNodeCos.h"
#include "UIMaterialNodeSin.h"
#include "UIMaterialNodeAbs.h"
#include "UIMaterialNodeDdx.h"
#include "UIMaterialNodeDdy.h"
#include "UIMaterialNodeDegree.h"
#include "UIMaterialNodeRadian.h"
#include "UIMaterialNodeFloor.h"
#include "UIMaterialNodeRound.h"
#include "UIMaterialNodeSqrt.h"
#include "UIMaterialNodeLogE.h"
#include "UIMaterialNodeLog2.h"
#include "UIMaterailNodeLog10.h"
#include "UIMaterialNodeExp2.h"
#include "UIMaterialNodeExpE.h"
#include "UIMaterialNodeReciprocal.h"
#include "UIMaterialNodeNoise.h"
#include "UIMaterialNodeCeil.h"
#include "UIMaterialNodeMul.h"
#include "UIMaterialNodeAdd.h"
#include "UIMaterialNodeSub.h"
#include "UImaterialNodeDiv.h"
#include "UIMaterialNodeMax.h"
#include "UIMaterialNodeMin.h"
#include "UIMaterialNodePow.h"
#include "UIMaterialNodeFmod.h"
#include "UIMaterialNodeLerp.h"
#include "UIMaterialNodeSaturate.h"
#include "UIMaterialNodeLit.h"
#include "UIMaterialNodeClamp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MainFrm.h"
#include "D3D9DockWnd.h"


// CShaderEditorView

IMPLEMENT_DYNCREATE(CShaderEditorView, CTabView)

BEGIN_MESSAGE_MAP(CShaderEditorView, CTabView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_COMPILE_RUN, &CShaderEditorView::OnCompileRun)
END_MESSAGE_MAP()

// CShaderEditorView construction/destruction

CD3DView* CShaderEditorView::VSH_Canvas = NULL;
CD3DView* CShaderEditorView::PSH_Canvas = NULL;

CShaderEditorView::CShaderEditorView()
{
	// TODO: add construction code here

}

CShaderEditorView::~CShaderEditorView()
{
}

BOOL CShaderEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTabView::PreCreateWindow(cs);
}

// CShaderEditorView drawing

void CShaderEditorView::OnDraw(CDC* /*pDC*/)
{
	CShaderEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CShaderEditorView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();
}

void CShaderEditorView::OnRButtonUp(UINT  nFlags , CPoint point)
{

}

void CShaderEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CShaderEditorView diagnostics

#ifdef _DEBUG
void CShaderEditorView::AssertValid() const
{
	CTabView::AssertValid();
}

void CShaderEditorView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}

CShaderEditorDoc* CShaderEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShaderEditorDoc)));
	return (CShaderEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CShaderEditorView message handlers

int CShaderEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CCreateContext context;
	context.m_pNewViewClass = RUNTIME_CLASS(CD3DView);
	context.m_pCurrentDoc = GetDocument();

	int vsh = AddView(RUNTIME_CLASS(CD3DView), CString(_T("vertex shader")), IDR_VERSHAGDER_WND, &context);
	context.m_pNewViewClass = RUNTIME_CLASS(CD3DView);
	int psh = AddView(RUNTIME_CLASS(CD3DView), CString(_T("pixel shader")), IDR_PIXELSHADER_WND, &context);
	
	CMFCTabCtrl& tab = GetTabControl();
	CShaderEditorView::VSH_Canvas = (CD3DView*)tab.GetTabWnd(vsh);
	CShaderEditorView::PSH_Canvas = (CD3DView*)tab.GetTabWnd(psh);
	VSH_Canvas->m_shType = ShaderEditor::VSH_CODE;
	PSH_Canvas->m_shType = ShaderEditor::PSH_CODE;

	// for test
// 	ShaderEditor::SUIWindow* Image =  
// 		(ShaderEditor::SUIWindow*)VSH_Canvas->m_uis.CreateWnd<ShaderEditor::UINodeClamp>(100, 100, 120, 40, &VSH_Canvas->m_uis,
// 		CString(_T("TestBtn")), CString(_T("TestBtn")));
	// Image->SetImage(CString(_T("F:\\Picture\\……小\\OME.bmp")));
	return 0;
}

void CShaderEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CTabView::OnMouseMove(nFlags, point);
}

void CShaderEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTabView::OnLButtonDown(nFlags, point);
}

void CShaderEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTabView::OnLButtonUp(nFlags, point);
}

void CShaderEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CTabView::OnRButtonDown(nFlags, point);
}

void CShaderEditorView::OnCompileRun()
{
	TiXmlDocument *myDocument = new TiXmlDocument();
	TiXmlElement *RootElement = new TiXmlElement("Material");
	myDocument->LinkEndChild(RootElement);
	TiXmlElement *TextureNode = new TiXmlElement("Textures");
	RootElement->LinkEndChild(TextureNode);
	TiXmlElement *MatrixNode = new TiXmlElement("Matrix");
	RootElement->LinkEndChild(MatrixNode);
	TiXmlElement *EffectCodeNode = new TiXmlElement("Effect");
	RootElement->LinkEndChild(EffectCodeNode);

	// TODO: 在此添加命令处理程序代码
	CString str;
	// 需要调整一下接口，
	str += VSH_Canvas->m_uis.GenCode(VSH_Canvas->m_shType, TextureNode, MatrixNode);
	str += _T("\n");
	str += PSH_Canvas->m_uis.GenCode(PSH_Canvas->m_shType, TextureNode, MatrixNode);
	str += _T("\n");

	str += _T("technique DefaultTech \n{\npass P0\n{\n");

	// render state
	ShaderEditor::SRenderState& rs = ((CMainFrame*)AfxGetMainWnd())->m_propertyWnd.dlg._RenderState;


	if (rs._AlphaBlendEnable.GetLength())
	{
		CString s;
		s.Format(_T("AlphaBlendEnable = %s;\n"), rs._AlphaBlendEnable);
		str += s;
	}

	if (rs._AlphaFunc.GetLength())
	{
		CString s;
		s.Format(_T("AlphaFunc = %s;\n"), rs._AlphaFunc);
		str += s;
	}

	if (rs._AlphaRef.GetLength())
	{
		CString s;
		s.Format(_T("AlphaRef = %s;\n"), rs._AlphaRef);
		str += s;
	}

	if (rs._AlphaTestEnalbe.GetLength())
	{
		CString s;
		s.Format(_T("AlphaTestEnalbe = %s;\n"), rs._AlphaTestEnalbe);
		str += s;
	}

	if (rs._BlendOp.GetLength())
	{
		CString s;
		s.Format(_T("BlendOp = %s;\n"), rs._BlendOp);
		str += s;
	}

	if (rs._DestBlend.GetLength())
	{
		CString s;
		s.Format(_T("DestBlend = %s;\n"), rs._DestBlend);
		str += s;
	}

	if (rs._FillMode.GetLength())
	{
		CString s;
		s.Format(_T("FillMode = %s;\n"), rs._FillMode);
		str += s;
	}

	if (rs._ShadeMode.GetLength())
	{
		CString s;
		s.Format(_T("ShadeMode = %s;\n"), rs._ShadeMode);
		str += s;
	}

	if (rs._SrcBlend.GetLength())
	{
		CString s;
		s.Format(_T("SrcBlend = %s;\n"), rs._SrcBlend);
		str += s;
	}

	if (rs._ZEnable.GetLength())
	{
		CString s;
		s.Format(_T("ZEnable = %s;\n"), rs._ZEnable);
		str += s;
	}

	if (rs._ZFunc.GetLength())
	{
		CString s;
		s.Format(_T("ZFunc = %s;\n"), rs._ZFunc);
		str += s;
	}

	if (rs._ZWritEnable.GetLength())
	{
		CString s;
		s.Format(_T("ZWriteEnable = %s;\n"), rs._ZWritEnable);
		str += s;
	}

	str += _T(" VertexShader = compile ");
	if (rs._vshVersion.GetLength() == 0)
		rs._vshVersion = _T("vs_3_0");
	str += rs._vshVersion;
	str += _T(" VS_Main();\n");

	str += _T(" PixelShader = compile ");
	if (rs._pshVersion.GetLength() == 0)
		rs._pshVersion = _T("ps_3_0");
	str += rs._pshVersion;
	str += _T(" PS_Main();\n");
	
	str += _T("}\n}\n");

#ifdef _DEBUG
	CString fName;
	
	CStdioFile file;
	file.Open(_T("TestFile.hlsl"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	file.SetLength(0);
	file.WriteString(str);
	file.Close();
#endif

	int len = WideCharToMultiByte(CP_ACP, 0, str.GetString(), -1, NULL, 0, NULL, NULL);
	char* code = new char[len+1];
	ZeroMemory(code, sizeof(char)*(len + 1));
	WideCharToMultiByte(CP_ACP, 0, str.GetString(), -1, code, len, NULL, NULL);
	TiXmlText *CodeContent = new TiXmlText(code);
	EffectCodeNode->LinkEndChild(CodeContent);
	delete[] code;
	myDocument->SaveFile("Default.xml");

#ifdef _DEBUG
	// test load
	
#endif

	auto MainWnd = (CMainFrame*)AfxGetMainWnd();
	CD3D9DockWnd& preViewWnd = MainWnd->m_previewWnd;

	preViewWnd.LoadMaterial();
}
