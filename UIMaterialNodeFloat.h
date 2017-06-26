#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeFloat : public SUIWindow
	{
	public:
		UINodeFloat(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Float"));
			m_nodeType->ShowBorder(TRUE);

			m_body = new SUIFloatLabel(x, y + heigth * 2, width, 40, UIDrawParams::DefaultBorderWidth, this);
			m_body->ShowBorder(TRUE);
			m_body->Name = _T("[ 0.0 ]");


			float OutY = y + heigth * 2 + 5;

			SUIButton* OutputX = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputX->Name = CString(_T("x"));
			OutputX->ID = UIMgr::GenerateUIID();
			OutputX->Usage = SUIButton::LINK_OUT;
		}

		virtual ~UINodeFloat()
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

			M_FLOAT = m_body->m_value;

			for each (auto ptr in Children)
			{
				ptr->Draw(device, font);
			}
		}

		virtual CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString str;
			str.Format(_T("float %s = %3.3ff;"), Name ,M_FLOAT);

			return str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUIFloatLabel* m_body = NULL;
		float M_FLOAT = 0.0f;
	};
}