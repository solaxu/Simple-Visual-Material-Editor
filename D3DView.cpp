// D3DScrollView.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "D3DView.h"

#include <algorithm>

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
#include "UIMaterialNodeTan.h"
#include "UIMaterialNodeInput.h"
#include "UIMaterialNodeOutput.h"
#include "UIMaterialNodeCode.h"


// CD3DView

IMPLEMENT_DYNCREATE(CD3DView, CView)

CD3DView::CD3DView():m_linkBtnCur(NULL),m_timerIndex(1),m_wndCur(NULL)
{

}

CD3DView::~CD3DView()
{
}


BEGIN_MESSAGE_MAP(CD3DView, CView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()

	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DISCONNECT, &CD3DView::OnDisconnect)
	ON_COMMAND(ID_MATRIX_WORLDMATRIX32906, &CD3DView::OnMatrixWorldmatrix32906)
	ON_COMMAND(ID_MATRIX_VIEWMATRIX, &CD3DView::OnMatrixViewmatrix)
	ON_COMMAND(ID_MATRIX_PROJECTMATRIX, &CD3DView::OnMatrixProjectmatrix)
	ON_COMMAND(ID_MATRIX_INVERSEWORLDMATRIX, &CD3DView::OnMatrixInverseworldmatrix)
	ON_COMMAND(ID_MATRIX_INVERSEVIEWMATRIX, &CD3DView::OnMatrixInverseviewmatrix)
	ON_COMMAND(ID_MATRIX_INVERSEPROJECTMATRIX, &CD3DView::OnMatrixInverseprojectmatrix)
	ON_COMMAND(ID_MATRIX_WORLDVIEWMATRIX, &CD3DView::OnMatrixWorldviewmatrix)
	ON_COMMAND(ID_MATRIX_WORLDVIEWPROJECTMATRIX, &CD3DView::OnMatrixWorldviewprojectmatrix)
	ON_COMMAND(ID_MATRIX_INVERSEWORLDVIEWMATRIX, &CD3DView::OnMatrixInverseworldviewmatrix)
	ON_COMMAND(ID_MATRIX_INVERSEWORLDVIEWPROJECTMATRIX32907, &CD3DView::OnMatrixInverseworldviewprojectmatrix32907)
	ON_COMMAND(ID_MATRIX_TRANSPOSE, &CD3DView::OnMatrixTranspose)
	ON_COMMAND(ID_VECTOR_FLOAT, &CD3DView::OnVectorFloat)
	ON_COMMAND(ID_VECTOR_FLOAT2, &CD3DView::OnVectorFloat2)
	ON_COMMAND(ID_VECTOR_FLOAT3, &CD3DView::OnVectorFloat3)
	ON_COMMAND(ID_VECTOR_FLOAT5, &CD3DView::OnVectorFloat5)
	ON_COMMAND(ID_SAMPLER_SAMPLER2D, &CD3DView::OnSamplerSampler2d)
	ON_COMMAND(ID_VECTOROPERATIONS_APPEND32902, &CD3DView::OnVectoroperationsAppend32902)
	ON_COMMAND(ID_VECTOROPERATIONS_CROSSPRODUCT, &CD3DView::OnVectoroperationsCrossproduct)
	ON_COMMAND(ID_VECTOROPERATIONS_DOTPRODUCT, &CD3DView::OnVectoroperationsDotproduct)
	ON_COMMAND(ID_VECTOROPERATIONS_DISTANCE, &CD3DView::OnVectoroperationsDistance)
	ON_COMMAND(ID_VECTOROPERATIONS_LENGTH, &CD3DView::OnVectoroperationsLength)
	ON_COMMAND(ID_VECTOROPERATIONS_NORMALIZE, &CD3DView::OnVectoroperationsNormalize)
	ON_COMMAND(ID_VECTOROPERATIONS_REFLECT, &CD3DView::OnVectoroperationsReflect)
	ON_COMMAND(ID_VECTOROPERATIONS_REFRACT, &CD3DView::OnVectoroperationsRefract)
	ON_COMMAND(ID_VECTOROPERATIONS_TRANSFORM32909, &CD3DView::OnVectoroperationsTransform32909)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ARCSIN, &CD3DView::OnMathematicalfunctionsArcsin)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ARCCOS, &CD3DView::OnMathematicalfunctionsArccos)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ARCTAN, &CD3DView::OnMathematicalfunctionsArctan)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ADD, &CD3DView::OnMathematicalfunctionsAdd)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ABS, &CD3DView::OnMathematicalfunctionsAbs)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_CEIL, &CD3DView::OnMathematicalfunctionsCeil)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_CLAMP, &CD3DView::OnMathematicalfunctionsClamp)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_COS, &CD3DView::OnMathematicalfunctionsCos)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_DDX, &CD3DView::OnMathematicalfunctionsDdx)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_DDY, &CD3DView::OnMathematicalfunctionsDdy)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_DEGREE32848, &CD3DView::OnMathematicalfunctionsDegree32848)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_DIV, &CD3DView::OnMathematicalfunctionsDiv)
	ON_COMMAND(ID_EXP_EXPE, &CD3DView::OnExpExpe)
	ON_COMMAND(ID_EXP_EXP3, &CD3DView::OnExpExp3)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_MOD, &CD3DView::OnMathematicalfunctionsMod)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_FLOOR, &CD3DView::OnMathematicalfunctionsFloor)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_LIT, &CD3DView::OnMathematicalfunctionsLit)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_LERP, &CD3DView::OnMathematicalfunctionsLerp)
	ON_COMMAND(ID_LOG_EXP2, &CD3DView::OnLogExp2)
	ON_COMMAND(ID_LOG_LOG2, &CD3DView::OnLogLog2)
	ON_COMMAND(ID_LOG_LOG11, &CD3DView::OnLogLog11)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_MAX32847, &CD3DView::OnMathematicalfunctionsMax32847)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_MIN, &CD3DView::OnMathematicalfunctionsMin)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_MUL, &CD3DView::OnMathematicalfunctionsMul)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_NOISE, &CD3DView::OnMathematicalfunctionsNoise)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_POWER32846, &CD3DView::OnMathematicalfunctionsPower32846)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_RECIPROCAL, &CD3DView::OnMathematicalfunctionsReciprocal)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_ROUND, &CD3DView::OnMathematicalfunctionsRound)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_RADIAN, &CD3DView::OnMathematicalfunctionsRadian)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_SIN, &CD3DView::OnMathematicalfunctionsSin)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_SQRT, &CD3DView::OnMathematicalfunctionsSqrt)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_SATURATE32854, &CD3DView::OnMathematicalfunctionsSaturate32854)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_SUBTRACT, &CD3DView::OnMathematicalfunctionsSubtract)
	ON_COMMAND(ID_MATHEMATICALFUNCTIONS_TAN, &CD3DView::OnMathematicalfunctionsTan)
	ON_COMMAND(ID_EDIT_DEL_NODE, &CD3DView::OnEditDelNode)
	ON_COMMAND(ID_ADDNODE_INPUTNODE32912, &CD3DView::OnAddnodeInputnode32912)
	ON_COMMAND(ID_ADDNODE_OUTPUTNODE32913, &CD3DView::OnAddnodeOutputnode32913)
	ON_COMMAND(ID_ADDNODE_CODENODE, &CD3DView::OnAddnodeCodenode)
	ON_COMMAND(ID__RUN, &CD3DView::OnSingleViewRun)
END_MESSAGE_MAP()


// CD3DView 绘图

void CD3DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	InitDirect9();

	SetTimer(m_timerIndex, 20, NULL);
}

void CD3DView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CD3DView 诊断

#ifdef _DEBUG
void CD3DView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CD3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

BOOL CD3DView::InitDirect9()
{
	if (NULL == (m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 1024;
	d3dpp.BackBufferWidth = 2048;
	d3dpp.BackBufferCount = 1;

	if (FAILED(m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetSafeHwnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_d3d9Device)))
	{
		return FALSE;
	}

	if (FAILED(D3DXCreateFont(m_d3d9Device, 0,0,0,0,0,0,0,0,0,_T("Arial"), &m_font)))
	{
		return FALSE;
	}

	return TRUE;
}

void CD3DView::Draw()
{
// 
// 	ShaderEditor::UIRect::SUIVertexFMT vertices[4] = {
// 		{ 10.0f, 10.0f, 0.5f, 1.0f, (DWORD)ShaderEditor::UIColor::White },
// 		{ 20.0f, 10.0f, 0.5f, 1.0f, (DWORD)ShaderEditor::UIColor::White },
// 		{ 10.0f, 20.0f, 0.5f, 1.0f, (DWORD)ShaderEditor::UIColor::White },
// 		{ 20.0f, 20.0f, 0.5f, 1.0f, (DWORD)ShaderEditor::UIColor::White }
// 	};
// 
// 	DWORD indices[6] = {
// 		0,1,2,
// 		2,1,3
// 	};
// 
// 	m_d3d9Device->SetFVF(ShaderEditor::UIRect::SUIVertexFMT::FVF);
// 	m_d3d9Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,
// 		0, 4, 2, indices, D3DFMT_INDEX32, vertices, sizeof(ShaderEditor::UIRect::SUIVertexFMT));

	m_uis.Draw(m_d3d9Device, m_font);
}

// CD3DView 消息处理程序

// 销毁

void CD3DView::OnDestroy()
{
	ShaderEditor::SafeReleaseCOM<LPDIRECT3DDEVICE9>(m_d3d9Device);
	ShaderEditor::SafeReleaseCOM<LPDIRECT3D9>(m_d3d9);
	KillTimer(m_timerIndex);

	CView::OnDestroy();
}

void CD3DView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	if (IsWindowVisible() == FALSE)
		return;

	if (nIDEvent == m_timerIndex)
	{
		m_uis.Update();

		m_d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(255,255,255), 1.0f, 0);

		if (SUCCEEDED(m_d3d9Device->BeginScene()))
		{
			Draw();
			m_d3d9Device->EndScene();
		}
	}
	m_d3d9Device->Present(NULL, NULL, NULL, NULL);
}

void CD3DView::OnSize(UINT nType, int cx, int cy)
{

}

void CD3DView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	ShaderEditor::UIObject* ui = m_uis.GetControl();
	if (ui != NULL)
		ui->EditObject();
}

void CD3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);
	ShaderEditor::UpdateMouseState(rc, point.x, point.y, WM_MOUSEMOVE, nFlags);

	if ((nFlags & MK_LBUTTON) && M_LINKBTN == NULL)
	{
		M_LINKBTN = m_uis.GetLinkButton();
		if (M_LINKBTN && M_LINKBTN->IN_BTN.size() != 0)
		{
			M_LINKBTN = NULL;
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CD3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);
	ShaderEditor::UpdateMouseState(rc, point.x, point.y, WM_LBUTTONDOWN, nFlags);
	CView::OnLButtonDown(nFlags, point);
}

void CD3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);
	ShaderEditor::UpdateMouseState(rc, point.x, point.y, WM_LBUTTONUP, nFlags);

	m_curMouseX = ShaderEditor::G_MouseState.CurPos.X;
	m_curMouseY = ShaderEditor::G_MouseState.CurPos.Y;

	if (M_LINKBTN)
	{
		auto btn = m_uis.GetLinkButton();
		if (btn == NULL || btn == M_LINKBTN || btn->IN_BTN.size() ||
			(btn->Parent == M_LINKBTN->Parent))
		{
			M_LINKBTN = NULL;
		}
		else
		{
			if (btn->Usage == ShaderEditor::SUIButton::LINK_IN)
			{
				if (btn->IN_BTN.end() == std::find(btn->IN_BTN.begin(), btn->IN_BTN.end(), M_LINKBTN))
					btn->IN_BTN.push_back(M_LINKBTN);

				if (M_LINKBTN->OUT_BTN.end() == std::find(M_LINKBTN->OUT_BTN.begin(), M_LINKBTN->OUT_BTN.end(), btn))
					M_LINKBTN->OUT_BTN.push_back(btn);

			}

			else if (btn->Usage == ShaderEditor::SUIButton::LINK_OUT)
			{
				if (M_LINKBTN->IN_BTN.end() == std::find(M_LINKBTN->IN_BTN.begin(), M_LINKBTN->IN_BTN.end(), btn))
					M_LINKBTN->IN_BTN.push_back(btn);

				if (btn->OUT_BTN.end() == std::find(btn->OUT_BTN.begin(), btn->OUT_BTN.end(), M_LINKBTN))
					btn->OUT_BTN.push_back(M_LINKBTN);
			}
		}

		M_LINKBTN = NULL;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CD3DView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);
	ShaderEditor::UpdateMouseState(rc, point.x, point.y, WM_RBUTTONDOWN, nFlags);
	CView::OnRButtonDown(nFlags, point);
}

void CD3DView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);
	ShaderEditor::UpdateMouseState(rc, point.x, point.y, WM_RBUTTONUP, nFlags);

	ClientToScreen(&point);
	OnContextMenu(this, point);

	m_curMouseX = ShaderEditor::G_MouseState.CurPos.X;
	m_curMouseY = ShaderEditor::G_MouseState.CurPos.Y;

	CView::OnRButtonUp(nFlags, point);
}

void CD3DView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_EDIT);
	CMenu *popup = menu.GetSubMenu(0);
	//CRect rc;
	//popup->GetClientRect(&rc);
	popup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	m_linkBtnCur = m_uis.GetLinkButton();
	m_wndCur = m_uis.GetWindow();
}

void CD3DView::OnDisconnect()
{
	// TODO: 在此添加命令处理程序代码
	if (m_linkBtnCur == NULL)
		return;
	ShaderEditor::SUIWindow* wnd = dynamic_cast<ShaderEditor::SUIWindow*>(m_linkBtnCur->Parent);
	if (wnd != NULL)
	{
		if (m_linkBtnCur->Usage == ShaderEditor::SUIButton::LINK_IN)
		{
			if (m_linkBtnCur->IN_BTN.size())
			{
				auto outBtn = m_linkBtnCur->IN_BTN[0];
				auto outWnd = dynamic_cast<ShaderEditor::SUIWindow*>(outBtn->Parent);
				if (outWnd)
				{
					auto it = std::find(outWnd->M_OUTPUTS.begin(), outWnd->M_OUTPUTS.end(), outBtn);
					if (it != outWnd->M_OUTPUTS.end() && outWnd->M_OUTPUTS.size() == 1)
						outWnd->M_OUTPUTS.erase(it);
				}

				if (outBtn)
				{
					auto it = std::find(outBtn->OUT_BTN.begin(), outBtn->OUT_BTN.end(), m_linkBtnCur);
					if (it != outBtn->OUT_BTN.end())
						outBtn->OUT_BTN.erase(it);
				}

				m_linkBtnCur->IN_BTN.clear();
			}
			auto it = std::find(wnd->M_INPUTS.begin(), wnd->M_INPUTS.end(), m_linkBtnCur);
			if (it != wnd->M_INPUTS.end())
				wnd->M_INPUTS.erase(it);

		}
		else if (m_linkBtnCur->Usage == ShaderEditor::SUIButton::LINK_OUT)
		{
			for each (auto btn in m_linkBtnCur->OUT_BTN)
			{
				btn->IN_BTN.clear();
				auto inWnd = dynamic_cast<ShaderEditor::SUIWindow*>(btn->Parent);
				if (inWnd)
				{
					auto it = std::find(inWnd->M_INPUTS.begin(), inWnd->M_INPUTS.end(), btn);
					if (it != inWnd->M_INPUTS.end())
						inWnd->M_INPUTS.erase(it);
				}
			}
			m_linkBtnCur->OUT_BTN.clear();
			auto it = std::find(wnd->M_OUTPUTS.begin(), wnd->M_OUTPUTS.end(), m_linkBtnCur);
			if (it != wnd->M_OUTPUTS.end())
				wnd->M_OUTPUTS.erase(it);
		}
	}
	return;
}


void CD3DView::OnMatrixWorldmatrix32906()
{
	// TODO: 在此添加命令处理程序代码

	m_uis.CreateWnd<ShaderEditor::UINodeWorldMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis, 
		CString(_T("WorldMat")), m_uis.GenerateUIID());

}


void CD3DView::OnMatrixViewmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeViewMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("ViewMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixProjectmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeProjectMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("ProjMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixInverseworldmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInvWorldMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("InvWMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixInverseviewmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInvViewMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("InvVMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixInverseprojectmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInvProjMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("InvPMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixWorldviewmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeWorldViewMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("WVMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixWorldviewprojectmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeWorldViewProjMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("WVPMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixInverseworldviewmatrix()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInvWorldViewMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("InvWVMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixInverseworldviewprojectmatrix32907()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInvWorldViewProjMatrix>(m_curMouseX, m_curMouseY, 125, 40, &m_uis,
		CString(_T("InvWVPMat")), m_uis.GenerateUIID());
}


void CD3DView::OnMatrixTranspose()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeTranspose>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("Transpose")), m_uis.GenerateUIID());
}


void CD3DView::OnVectorFloat()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFloat>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("float")), m_uis.GenerateUIID());
}


void CD3DView::OnVectorFloat2()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFloat2>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("float2")), m_uis.GenerateUIID());
}


void CD3DView::OnVectorFloat3()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFloat3>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("float3")), m_uis.GenerateUIID());
}


void CD3DView::OnVectorFloat5()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFloat4>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("float4")), m_uis.GenerateUIID());
}


void CD3DView::OnSamplerSampler2d()
{
	// TODO: 在此添加命令处理程序代码
	auto tex = m_uis.CreateWnd<ShaderEditor::UINodeSampler2D>(m_curMouseX, m_curMouseY, 220, 40, &m_uis,
		CString(_T("sampler2d")), m_uis.GenerateUIID());
	(dynamic_cast<ShaderEditor::UINodeSampler2D*>(tex))->M_IMAGE->Image->Device = m_d3d9Device;
}


void CD3DView::OnVectoroperationsAppend32902()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeAppend>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("append")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsCrossproduct()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeCross>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("cross")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsDotproduct()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDot>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("dot")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsDistance()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDistance>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("distance")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsLength()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLength>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("length")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsNormalize()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeNormalize>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("normalize")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsReflect()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeReflect>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("reflect")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsRefract()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeRefract>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("refract")), m_uis.GenerateUIID());
}


void CD3DView::OnVectoroperationsTransform32909()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeTransform>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("transform")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsArcsin()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeArcsin>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("arcsin")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsArccos()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeArccos>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("arccos")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsArctan()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeArctan>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("arctan")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsAdd()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeAdd>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("add")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsAbs()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeAbs>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("abs")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsCeil()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeCeil>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("ceil")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsClamp()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeClamp>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("clamp")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsCos()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeCos>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("cos")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsDdx()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDdx>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("ddx")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsDdy()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDdy>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("ddy")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsDegree32848()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDegree>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("degree")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsDiv()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeDiv>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("div")), m_uis.GenerateUIID());
}


void CD3DView::OnExpExpe()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeExpE>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("exp e")), m_uis.GenerateUIID());
}


void CD3DView::OnExpExp3()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeExp2>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("exp 2")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsMod()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFmod>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("fmod")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsFloor()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeFloor>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("floor")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsLit()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLit>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("lit")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsLerp()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLerp>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("lerp")), m_uis.GenerateUIID());
}


void CD3DView::OnLogExp2()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLogE>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("log e")), m_uis.GenerateUIID());
}


void CD3DView::OnLogLog2()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLog2>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("log 2")), m_uis.GenerateUIID());
}


void CD3DView::OnLogLog11()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeLog10>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("log 10")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsMax32847()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeMax>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("max")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsMin()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeMin>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("min")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsMul()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeMul>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("mul")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsNoise()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeNoise>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("noise")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsPower32846()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodePow>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("pow")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsReciprocal()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeReciprocal>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("reciprocal")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsRound()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeRound>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("round")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsRadian()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeRadian>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("radian")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsSin()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeSin>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("sin")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsSqrt()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeSqrt>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("sqrt")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsSaturate32854()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeSaturate>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("saturate")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsSubtract()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeSub>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("sub")), m_uis.GenerateUIID());
}


void CD3DView::OnMathematicalfunctionsTan()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeTan>(m_curMouseX, m_curMouseY, 120, 40, &m_uis,
		CString(_T("tan")), m_uis.GenerateUIID());
}


void CD3DView::OnEditDelNode()
{
	// TODO: 在此添加命令处理程序代码
	if (m_wndCur)
	{
		// 清除该节点上的所有链接, 还需要清除连接到该节点上的链接

		for each(auto ptr in m_wndCur->Children)
		{
			ShaderEditor::SUIButton* btn = dynamic_cast<ShaderEditor::SUIButton*>(ptr);
			if (btn)
			{
				if (btn->Usage == ShaderEditor::SUIButton::LINK_IN)
				{
					if (btn->IN_BTN.size() != 0)
					{
						auto linkin = btn->IN_BTN[0];
						for (auto it = linkin->OUT_BTN.begin(); it != linkin->OUT_BTN.end(); ++it)
						{
							auto outBtn = *it;
							if (outBtn == btn)
							{
								linkin->OUT_BTN.erase(it);
								break;
							}
						}
					}
				}
				else if (btn->Usage == ShaderEditor::SUIButton::LINK_OUT)
				{
					for each(auto outBtn in btn->OUT_BTN)
					{
						outBtn->IN_BTN.clear();
					}
				}
			}
		}

		m_uis.DeleteUI(m_wndCur);
	}
}


void CD3DView::OnAddnodeInputnode32912()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeInput>(m_curMouseX, m_curMouseY, 200, 40, &m_uis,
		CString(_T("In")), m_uis.GenerateUIID());
}


void CD3DView::OnAddnodeOutputnode32913()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeOutput>(m_curMouseX, m_curMouseY, 200, 40, &m_uis,
		CString(_T("Out")), m_uis.GenerateUIID());
}


void CD3DView::OnAddnodeCodenode()
{
	// TODO: 在此添加命令处理程序代码
	m_uis.CreateWnd<ShaderEditor::UINodeCode>(m_curMouseX, m_curMouseY, 200, 40, &m_uis,
		CString(_T("Code")), m_uis.GenerateUIID());
}

void CD3DView::OnSingleViewRun()
{
	if (!this->IsWindowVisible())
		return;
	m_Code = m_uis.GenCode(m_shType, NULL, NULL);

	// 测试输出到文件
#ifdef _DEBUG
	CString fName;
	if (m_shType == ShaderEditor::CODE_GEN::PSH_CODE)
		fName = _T("./psh_test.txt");
	else
		fName = _T("./vsh_test.txt");
	CStdioFile file;
	file.Open(fName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	file.SetLength(0);
	file.WriteString(m_Code);
	file.Close();
#endif
}
