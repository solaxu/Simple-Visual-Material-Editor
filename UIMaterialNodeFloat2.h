#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeFloat2 : public SUIWindow
	{
	public:
		UINodeFloat2(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Float2"));
			m_nodeType->ShowBorder(TRUE);

			m_X = new SUIFloatLabel(x, y + heigth * 2, width, 60, UIDrawParams::DefaultBorderWidth, this);
			m_Y = new SUIFloatLabel(x, y + heigth * 2 + 60, width, 60, UIDrawParams::DefaultBorderWidth, this);

			M_FLOAT0 = 0.0;
			M_FLOAT1 = 0.0;

			m_X->ShowBorder(TRUE);
			m_Y->ShowBorder(TRUE);

			m_X->Name = _T("[ 0.0 ]");
			m_Y->Name = _T("[ 0.0 ]");

			float OutY = y + heigth * 2 + 5;

			SUIButton* OutputX = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputX->Name = CString(_T("x"));
			OutputX->ID = UIMgr::GenerateUIID();
			OutputX->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputY = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputY->Name = CString(_T("y"));
			OutputY->ID = UIMgr::GenerateUIID();
			OutputY->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputXY = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputXY->Name = CString(_T("xy"));
			OutputXY->ID = UIMgr::GenerateUIID();
			OutputXY->Usage = SUIButton::LINK_OUT;

			isStruct = TRUE;
		}

		virtual ~UINodeFloat2()
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

			M_FLOAT0 = m_X->m_value;
			M_FLOAT1 = m_Y->m_value;

			for each (auto ptr in Children)
			{
				ptr->Draw(device, font);
			}
		}

		virtual CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString str;

			str.Format(_T("float2 %s = float2(%3.3ff, %3.3ff);"), Name, M_FLOAT0, M_FLOAT1);

			return str;
		}

		virtual CString SyntaxTreeGenCode(DWORD sh /* = PSH_CODE */)
		{
			return _T("");
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUIFloatLabel* m_X = NULL;
		SUIFloatLabel* m_Y = NULL;
		float M_FLOAT0 = 0.0f;
		float M_FLOAT1 = 0.0f;
	};
}