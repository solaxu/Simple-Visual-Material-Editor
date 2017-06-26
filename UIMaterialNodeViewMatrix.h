#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeViewMatrix : public SUIWindow
	{
	public:
		UINodeViewMatrix(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("ViewMat4"));
			m_nodeType->ShowBorder(TRUE);

			m_body = new SUILabel(x, y + heigth * 2, width, 40, UIDrawParams::DefaultBorderWidth, this);
			m_body->ShowBorder(TRUE);


			float OutY = y + heigth * 2 + 5;

			SUIButton* Output = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			Output->Name = CString(_T("mat"));
			Output->ID = UIMgr::GenerateUIID();
			Output->Usage = SUIButton::LINK_OUT;
		}

		virtual ~UINodeViewMatrix()
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

		virtual CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString str;

			str.Format(_T("float4x4 %s;"), Name);

			return str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;
	};
}