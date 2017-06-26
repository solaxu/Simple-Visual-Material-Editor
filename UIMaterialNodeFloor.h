#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeFloor : public SUIWindow
	{
	public:
		UINodeFloor(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Floor"));
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

		virtual ~UINodeFloor()
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

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;
	};
}