#include "stdafx.h"
#include "UIMgr.h"
#include "UIMaterialNodeCode.h"
#include "UIMaterialNodeInput.h"
#include "UIMaterialNodeOutput.h"
#include "UIMaterialNodeSampler2D.h"
#include "UIMaterialNodeViewMatrix.h"
#include "UIMaterialNodeWorldMatrix.h"
#include "UIMaterialNodeProjectMat.h"
#include "UIMaterialNodeWorldViewMatrix.h"
#include "UIMaterialNodeWorldViewProjMatrix.h"
#include "UIMaterialNodeInvWorldMatrix.h"
#include "UIMaterialNodeInvProjMatrix.h"
#include "UIMaterialNodeInvWOrldViewMatrix.h"
#include "UIMaterialNodeInvWorldViewProjMatrix.h"
#include "UIMaterialNodeInvView.h"

namespace ShaderEditor
{
	DWORD UIMgr::m_idSeed = 1;

	UIMgr::UIMgr()
	{

	}

	UIMgr::~UIMgr()
	{
		for (int i = 0; i < m_wnds.size(); ++i)
		{
			if (m_wnds[i])
			{
				delete m_wnds[i];
				m_wnds[i] = NULL;
			}
		}
	}

	void UIMgr::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		for each (auto ptr in m_wnds)
		{
			if (ptr)
			{
				ptr->Draw(device, font);
			}
		}
		CollectLinkLines(device);
	}


	void UIMgr::DeleteUI(UIObject* obj)
	{
		for (auto it = m_wnds.begin(); it != m_wnds.end(); ++it)
		{
			auto ptr = *it;
			if (ptr == obj)
			{
				m_wnds.erase(it);
				return;
			}
		}
	}

	void UIMgr::DeleteUI(CString& id)
	{
		for (auto it = m_wnds.begin(); it != m_wnds.end(); ++it)
		{
			auto ptr = *it;
			if (ptr->ID == id)
			{
				m_wnds.erase(it);
				return;
			}
		}
	}

	UIObject* UIMgr::GetUI(CString& id)
	{
		for (auto it = m_wnds.begin(); it != m_wnds.end(); ++it)
		{
			auto ptr = *it;
			if (ptr->ID == id)
			{
				return ptr;
			}
		}
		return NULL;
	}

	void UIMgr::Update()
	{
		// 处理消息
		for each(auto ptr in m_wnds)
		{
			// 窗口重叠情况下需要做特殊处理
			if (G_MouseState.Message == WM_MOUSEMOVE && G_MouseState.wParam & MK_LBUTTON)
			{
				if (ptr->CheckMouse(G_MouseState.CurPos.X, G_MouseState.CurPos.Y))
				{
					ptr->OnMouse(ShaderEditor::G_MouseState);
					break;
				}
			}
			else
				ptr->OnMouse(ShaderEditor::G_MouseState);
		}
	}

	SUIButton* UIMgr::GetLinkButton()
	{
		for each (auto ptr in m_wnds)
		{
			for each (auto ctrl in ptr->Children)
			{
				SUIButton* btn = dynamic_cast<SUIButton*>(ctrl);

				if (btn != NULL)
				{
					if (btn->CheckMouse(G_MouseState.CurPos.X, G_MouseState.CurPos.Y))
					{
						return btn;
					}
				}
			}
		}
		return NULL;
	}

	UIObject* UIMgr::GetControl()
	{
		for each (auto ptr in m_wnds)
		{
			if (ptr->CheckMouse(G_MouseState.CurPos.X, G_MouseState.CurPos.Y))
				return ptr;
			for each (auto ctrl in ptr->Children)
			{
				if (ctrl->CheckMouse(G_MouseState.CurPos.X, G_MouseState.CurPos.Y))
				{
					return ctrl;
				}
			}
		}
		return NULL;
	}

	SUIWindow* UIMgr::GetWindow()
	{
		for each (auto ptr in m_wnds)
		{
			SUIWindow* wnd = dynamic_cast<SUIWindow*>(ptr);
			if (wnd->CheckMouse(G_MouseState.CurPos.X, G_MouseState.CurPos.Y))
			{
				return wnd;
			}
		}
		return NULL;
	}

	// 应当考虑到在构建联通信息的时候，需要防止重复遍历的内容，因此应该考虑到SUIbutton方位标志位
	void UIMgr::CollectLinkLines(LPDIRECT3DDEVICE9 device)
	{
		std::vector<LinksPoint> points;
		for (int i = 0; i < m_wnds.size(); ++i)
		{
			SUIWindow* wnd = dynamic_cast<SUIWindow*>(m_wnds[i]);
			for (auto ptr : wnd->M_OUTPUTS)
			{
				SUIButton* linkBtn = dynamic_cast<SUIButton*>(ptr);
				if (NULL != linkBtn)
				{
					float sx = linkBtn->Left + linkBtn->Width * 0.5f;
					float sy = linkBtn->Top + linkBtn->Height * 0.5f;
					// 只关心out->in
					if (linkBtn->Usage == SUIButton::LINK_OUT)
					{
						// 对于它连接到的所有的out button都写上去
						for (auto outBtn : linkBtn->OUT_BTN)
						{
							LinksPoint pt;
							float ex = outBtn->Left + outBtn->Width * 0.5f;
							float ey = outBtn->Top + outBtn->Height * 0.5f;

							pt.x = sx; pt.y = sy;
							points.push_back(pt);

							pt.x = ex; pt.y = ey;
							points.push_back(pt);
						}
					}
				}
			}
		}

		//
		if (device && points.size())
		{
			LinksPoint* pts = new LinksPoint[points.size()];

			for (int i = 0; i < points.size(); ++i)
			{
				pts[i].x = points[i].x;
				pts[i].y = points[i].y;
				pts[i].z = points[i].z;
				pts[i].w = points[i].w;
				pts[i].diffuse = points[i].diffuse;
			}

			HRESULT hr = device->SetFVF(LinksPoint::FVF);
			if (FAILED(device->DrawPrimitiveUP(D3DPT_LINELIST, points.size() / 2, (void*)pts,
				sizeof(LinksPoint) )))
			{
				// test
				MessageBox(NULL, _T("asdd"), _T("sd"), MB_OK);
				return;
			}

			delete [] pts;
		}
		return;
	}

	CString UIMgr::GenCode(DWORD sh /* = PSH_CODE */, TiXmlElement* texNode, TiXmlElement* matrixNode)
	{
		// 首先处理所有入度为0的点，Code节点需要提取其包含的代码
		CString str;
		ShaderEditor::UINodeInput* MainWnd = NULL;
		for each(auto ptr in m_wnds)
		{
			auto wnd = dynamic_cast<ShaderEditor::SUIWindow*>(ptr);
			if (wnd)
			{
				auto codeNode = dynamic_cast<ShaderEditor::UINodeCode*>(wnd);
				if (codeNode)
				{
					str += codeNode->m_code;
				}
				auto samplerNode = dynamic_cast<ShaderEditor::UINodeSampler2D*>(wnd);
				if (samplerNode)
				{
					str += samplerNode->GenCode(sh);
					if (texNode)
					{
						// 创建一个Texure的Element并加入进去
						CString path = samplerNode->M_IMAGE->Image->ImagePath;
						int len = WideCharToMultiByte(CP_ACP, 0, samplerNode->Name.GetString(), -1, NULL, 0, NULL, NULL);
						char* cname = new char[len + 1];
						ZeroMemory(cname, sizeof(char)*(len + 1));
						WideCharToMultiByte(CP_ACP, 0, samplerNode->Name.GetString(), -1, cname, len, NULL, NULL);
						TiXmlElement* texElem = new TiXmlElement(cname);
						delete[] cname;
						texNode->LinkEndChild(texElem);

						len = WideCharToMultiByte(CP_ACP, 0, path.GetString(), -1, NULL, 0, NULL, NULL);
						char* cpath = new char[len + 1];
						ZeroMemory(cpath, sizeof(char)*(len + 1));
						WideCharToMultiByte(CP_ACP, 0, path.GetString(), -1, cpath, len, NULL, NULL);
						TiXmlText *CodeContent = new TiXmlText(cpath);
						texElem->LinkEndChild(CodeContent);
						delete[] cpath;
					}
				}
				// 需要搜集一下Sampler的信息以及Matrix的信息
				wnd->M_VISITED = FALSE;
				// 拿到所有入度为0的节点，同时丢弃掉出度为0的节点
				if (wnd->M_INPUTS.size() == 0 && wnd->M_OUTPUTS.size() != 0)
				{
					
					if (MainWnd == NULL)
						MainWnd = dynamic_cast<ShaderEditor::UINodeInput*>(wnd);
					
					if ((ShaderEditor::SUIWindow*)MainWnd != wnd && (ShaderEditor::SUIWindow*)wnd != samplerNode)
					{
						str += wnd->GenCode(sh);
						// 创建一个Matrix ELement并加入进去
						auto pViewMat = dynamic_cast<UINodeViewMatrix*>(wnd);
						auto pWorldMat = dynamic_cast<UINodeWorldMatrix*>(wnd);
						auto pProjMat = dynamic_cast<UINodeProjectMatrix*>(wnd);
						auto pWorldViewMat = dynamic_cast<UINodeWorldViewMatrix*>(wnd);
						auto pWorldViewProjMat = dynamic_cast<UINodeWorldViewProjMatrix*>(wnd);

						auto pInvViewMat = dynamic_cast<UINodeInvViewMatrix*>(wnd);
						auto pInvWorldMat = dynamic_cast<UINodeInvWorldMatrix*>(wnd);
						auto pInvProjMat = dynamic_cast<UINodeInvProjMatrix*>(wnd);
						auto pInvWorldViewMat = dynamic_cast<UINodeInvWorldViewMatrix*>(wnd);
						auto pInvWorldViewProjMat = dynamic_cast<UINodeInvWorldViewProjMatrix*>(wnd);

						if (pViewMat || pWorldMat || pWorldViewMat || pWorldViewProjMat ||
							pProjMat || pInvProjMat || pInvWorldViewProjMat || pInvWorldMat ||
							pInvProjMat || pInvViewMat)
						{
							if (matrixNode != NULL)
							{
								int len = WideCharToMultiByte(CP_ACP, 0, wnd->Name.GetString(), -1, NULL, 0, NULL, NULL);
								char* cname = new char[len + 1];
								ZeroMemory(cname, sizeof(char)*(len + 1));
								WideCharToMultiByte(CP_ACP, 0, wnd->Name.GetString(), -1, cname, len, NULL, NULL);
								TiXmlElement* texElem = new TiXmlElement(cname);
								delete[] cname;
								matrixNode->LinkEndChild(texElem);
							}
						}
					}
					str += _T("\n");
				}
			}
		}

		if (MainWnd == NULL)
			return _T("");

		// 然后处理输出节点结构
		UINodeOutput* OutWnd = NULL;
		for each(auto ptr in m_wnds)
		{
			auto wnd = dynamic_cast<ShaderEditor::SUIWindow*>(ptr);
			if (wnd)
			{
				// 拿到所有出度为0的节点，同时丢弃掉入度为0的节点
				if (wnd->M_INPUTS.size() != 0 && wnd->M_OUTPUTS.size() == 0)
				{
					OutWnd = dynamic_cast<ShaderEditor::UINodeOutput*>(wnd);
					if (OutWnd)
					{
						str += OutWnd->GetStruct(sh);
						str += _T("\n");
						break;
					}
				}
			}
		}

		if (MainWnd == NULL || OutWnd == NULL)
			return _T("");

		str += MainWnd->GetStruct(sh);

		str += _T("\n");
		str += MainWnd->GenCode(sh);

		str += _T("\n{\n");
		if (PSH_CODE == sh)
			str += _T("PS_OUTPUT Out = (PS_OUTPUT)0;\n\n");
		else
			str += _T("VS_OUTPUT Out = (VS_OUTPUT)0;\n\n");

		str += OutWnd->SyntaxTreeGenCode(sh);

// 		for each(auto ptr in m_wnds)
// 		{
// 			auto wnd = dynamic_cast<ShaderEditor::SUIWindow*>(ptr);
// 			if (wnd)
// 			{
// 				// 正常节点
// 				if (wnd->M_INPUTS.size() != 0 && wnd->M_OUTPUTS.size() != 0)
// 				{
// 					str += wnd->GenCode(sh);
// 					str += _T("\n");
// 				}
// 			}
// 		}

		str += _T("return Out;\n}\n");

		return str;
	}
}