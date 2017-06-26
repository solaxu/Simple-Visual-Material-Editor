#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeTranspose : public SUIWindow
	{
	public:
		UINodeTranspose(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Transpose"));
			m_nodeType->ShowBorder(TRUE);

			m_body = new SUILabel(x, y + heigth * 2, width, 120, UIDrawParams::DefaultBorderWidth, this);
			m_body->ShowBorder(TRUE);


			float OutY = y + heigth * 2 + 5;

			SUIButton* Output = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			Output->Name = CString(_T("mat"));
			Output->ID = UIMgr::GenerateUIID();
			Output->Usage = SUIButton::LINK_OUT;

			SUIButton* Input = new SUIButton(x + Width, OutY, 40, 20, 2, this);
			Input->Name = CString(_T("mat"));
			Input->ID = UIMgr::GenerateUIID();
			Input->Usage = SUIButton::LINK_IN;
		}

		virtual ~UINodeTranspose()
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

		virtual CString SyntaxTreeGenCode(DWORD sh /* = PSH_CODE */)
		{
			CString s;

			CString str = _T("float4x4 ");
			str += Name;
			str += _T(" = transpose(");

			if (M_INPUTS.size())
			{
				auto btn = dynamic_cast<SUIButton*>(M_INPUTS[0]);
				auto IN_WND = dynamic_cast<SUIWindow*>(btn->IN_BTN[0]->Parent);

				if (IN_WND)
				{
					s = IN_WND->SyntaxTreeGenCode(sh);
					str += IN_WND->Name;
				}
			}
			str += _T(");\n");

			return s + str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;
	};
}