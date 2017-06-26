#pragma once

#include "UIMgr.h"

namespace ShaderEditor
{
	class UINodeFloat3 : public SUIWindow
	{
	public:
		UINodeFloat3(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Float3"));
			m_nodeType->ShowBorder(TRUE);

			m_X = new SUIFloatLabel(x, y + heigth * 2, width, 50, UIDrawParams::DefaultBorderWidth, this);
			m_X->ShowBorder(TRUE);
			m_X->Name = _T("[ 0.0 ]");

			m_Y = new SUIFloatLabel(x, y + heigth * 2 + 50, width, 50, UIDrawParams::DefaultBorderWidth, this);
			m_Y->ShowBorder(TRUE);
			m_Y->Name = _T("[ 0.0 ]");

			m_Z = new SUIFloatLabel(x, y + heigth * 2 + 100, width, 50, UIDrawParams::DefaultBorderWidth, this);
			m_Z->ShowBorder(TRUE);
			m_Z->Name = _T("[ 0.0 ]");


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
			SUIButton* OutputZ = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputZ->Name = CString(_T("z"));
			OutputZ->ID = UIMgr::GenerateUIID();
			OutputZ->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputXY = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputXY->Name = CString(_T("xy"));
			OutputXY->ID = UIMgr::GenerateUIID();
			OutputXY->Usage = SUIButton::LINK_OUT;

			OutY += 30.0f;
			SUIButton* OutputXYZ = new SUIButton(x - 40, OutY, 40, 20, 2, this);
			OutputXYZ->Name = CString(_T("xyz"));
			OutputXYZ->ID = UIMgr::GenerateUIID();
			OutputXYZ->Usage = SUIButton::LINK_OUT;

			isStruct = TRUE;
		}

		virtual ~UINodeFloat3()
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
			M_FLOAT2 = m_Z->m_value;

			for each (auto ptr in Children)
			{
				ptr->Draw(device, font);
			}
		}

		virtual CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString str;

			str.Format(_T("float3 %s = float3(%3.3ff, %3.3ff, %3.3ff);"), Name, M_FLOAT0, M_FLOAT1, M_FLOAT2);

			return str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUIFloatLabel* m_X = NULL;
		SUIFloatLabel* m_Y = NULL;
		SUIFloatLabel* m_Z = NULL;
		float M_FLOAT0 = 0.0f;
		float M_FLOAT1 = 0.0f;
		float M_FLOAT2 = 0.0f;
	};
}