#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeSampler2D : public SUIWindow
	{
	public:
		UINodeSampler2D(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Sampler2D"));
			m_nodeType->ShowBorder(TRUE);

			M_IMAGE = new SUIImage(x, y + heigth * 2, 220, 220, UIDrawParams::DefaultBorderWidth, this);


			float OutY = y + heigth * 2 + 5;
			float InY = OutY;

			SUIButton* InputUV = new SUIButton(x + 220, InY, 40, 20, 2, this);
			InputUV->Name = CString(_T("uv"));
			InputUV->ID = UIMgr::GenerateUIID();
			InputUV->Usage = SUIButton::LINK_IN;

			SUIButton* OutputR = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputR->Name = CString(_T("r"));
			OutputR->ID = UIMgr::GenerateUIID();
			OutputR->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputG = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputG->Name = CString(_T("g"));
			OutputG->ID = UIMgr::GenerateUIID();
			OutputG->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputB = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputB->Name = CString(_T("b"));
			OutputB->ID = UIMgr::GenerateUIID();
			OutputB->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputA = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputA->Name = CString(_T("a"));
			OutputA->ID = UIMgr::GenerateUIID();
			OutputA->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputRG = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputRG->Name = CString(_T("rg"));
			OutputRG->ID = UIMgr::GenerateUIID();
			OutputRG->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputRGB = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputRGB->Name = CString(_T("rgb"));
			OutputRGB->ID = UIMgr::GenerateUIID();
			OutputRGB->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputRGBA = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputRGBA->Name = CString(_T("rgba"));
			OutputRGBA->ID = UIMgr::GenerateUIID();
			OutputRGBA->Usage = SUIButton::LINK_OUT;

			isStruct = TRUE;
		}

		virtual ~UINodeSampler2D()
		{
			for each (auto ptr in Children)
			{
				if (ptr)
				{
					delete ptr;
					ptr = NULL;
				}
			}
		}

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
		{
			SUIWindow::Draw(device, font);

			for each (auto ptr in Children)
			{
				ptr->Draw(device, font);
			}
		}

		virtual void SetImage(CString& path)
		{
			M_IMAGE->SetTexture(path);
		}

		virtual CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString s = _T("texture ");
			s += Name;
			s += _T("Tex;\n\n");
			
			CString temp;
			temp.Format(_T("sampler Sampler%s = sampler_state\n{\nTexture = %sTex;\n"), Name, Name);
			s += temp;
			temp = _T("");

			// sampler states
			temp.Format(_T("AddressU = %s;\n"), M_IMAGE->m_samplerState.addressU);
			s += temp;
			temp = _T("");

			temp.Format(_T("AddressV = %s;\n"), M_IMAGE->m_samplerState.addressV);
			s += temp;
			temp = _T("");

			temp.Format(_T("AddressW = %s;\n"), M_IMAGE->m_samplerState.addressW);
			s += temp;
			temp = _T("");

			temp.Format(_T("MipFilter = %s;\n"), M_IMAGE->m_samplerState.mipFilter);
			s += temp;
			temp = _T("");

			temp.Format(_T("MinFilter = %s;\n"), M_IMAGE->m_samplerState.minFilter);
			s += temp;
			temp = _T("");

			temp.Format(_T("MagFilter = %s;\n"), M_IMAGE->m_samplerState.magFilter);
			s += temp;
			temp = _T("");

			s += _T("};\n");

			return s;
		}

		virtual CString SyntaxTreeGenCode(DWORD sh /* = PSH_CODE */)
		{

			CString s;

			CString str = _T("float4 ");
			str += Name;
			str += _T(" = tex2D(");
			CString temp;
			temp.Format(_T("Sampler%s"),Name);
			str += temp;
			str += _T(", ");

			int i = 0;
			for each (auto ptr in M_INPUTS)
			{
				auto btn = dynamic_cast<SUIButton*>(ptr);
				auto IN_WND = dynamic_cast<SUIWindow*>(btn->IN_BTN[0]->Parent);

				if (IN_WND)
				{
					if (!IN_WND->M_VISITED)
						s += IN_WND->SyntaxTreeGenCode(sh);
					if (IN_WND->isStruct)
					{
						str += IN_WND->Name;
						str += _T(".");
						str += btn->IN_BTN[0]->Name;
					}
					else
						str += IN_WND->Name;
					++i;
				}
			}
			str += _T(");\n");

			M_VISITED = TRUE;

			return s + str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUIImage* M_IMAGE = NULL;
	};
}