#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeLogE : public SUIWindow
	{
	public:
		UINodeLogE(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Log e"));
			m_nodeType->ShowBorder(TRUE);

			m_body = new SUILabel(x, y + heigth * 2, width, 40, UIDrawParams::DefaultBorderWidth, this);
			m_body->ShowBorder(TRUE);


			float InY = y + heigth * 2 + 5;
			float OutY = InY;

			SUIButton* inputX = new SUIButton(x + width, InY, 40, 20, 2, this);
			InY += 30;
			inputX->Name = CString(_T("f"));
			inputX->ID = UIMgr::GenerateUIID();
			inputX->Usage = SUIButton::LINK_IN;

			//////////////////////////////////////////////////////////////////////////

			SUIButton* OutputX = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutY += 30;
			OutputX->Name = CString(_T("f"));
			OutputX->ID = UIMgr::GenerateUIID();
			OutputX->Usage = SUIButton::LINK_OUT;
		}

		virtual ~UINodeLogE()
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

			CString str = _T("float ");
			str += Name;
			str += _T(" = log(");

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

			return s + str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;
	};
}