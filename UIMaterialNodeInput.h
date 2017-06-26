#pragma once

#include "UI.h"
#include "UIMgr.h"
#include "InoutputDlg.h"
#include <vector>

using std::vector;

namespace ShaderEditor
{
	class UINodeInput : public SUIWindow
	{
	public:
		UINodeInput(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Input"));
			m_nodeType->ShowBorder(TRUE);

			isStruct = TRUE;
// 			float InY = y + heigth * 2 + 5;
// 			float OutY = InY;
// 
// 			//////////////////////////////////////////////////////////////////////////
// 
// 			SUIButton* OutputX = new SUIButton(x - 40, OutY, 40, 20, 2, this);
// 			OutY += 30;
// 			OutputX->Name = CString(_T("f"));
// 			OutputX->ID = UIMgr::GenerateUIID();
// 			OutputX->Usage = SUIButton::LINK_OUT;
		}

		virtual ~UINodeInput()
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

		void Update()
		{
			if (m_body)
			{
				delete m_body;
				m_body = NULL;
			}

			for each(auto obj in Children)
			{
				delete obj;
				obj = NULL;
			}

			Children.clear();

			m_nodeType = new SUILabel(Left, Top + Height, Width, Height, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Input"));
			m_nodeType->ShowBorder(TRUE);

			float OutY = Top + Height * 2 + 5;

			for (int i = 0; i < m_count; ++i)
			{
				CString s;
				s.Format(_T("%s:%s"), M_TYPES[i], M_SEMANTICS[i]);
				SUILabel* label = new SUILabel(Left, Top + Height * (2 + i), Width, Height, UIDrawParams::DefaultBorderWidth, this);
				label->ShowBorder(TRUE);
				label->Name = s;

				SUIButton* OutputX = new SUIButton(Left - 40, OutY, 40, 20, 2, this);
				OutY += 30;
				OutputX->Name = M_NAMES[i];
				OutputX->ID = UIMgr::GenerateUIID();
				OutputX->Usage = SUIButton::LINK_OUT;
			}
		}

		void EditObject()
		{
			CInoutputDlg dlg;
			dlg.M_NAMES = M_NAMES;
			dlg.M_TYPES = M_TYPES;
			dlg.M_SEMANTICS = M_SEMANTICS;
			dlg.m_count = m_count;

			if (IDOK == dlg.DoModal())
			{
				M_NAMES = dlg.M_NAMES;
				M_TYPES = dlg.M_TYPES;
				M_SEMANTICS = dlg.M_SEMANTICS;
				m_count = dlg.m_count;
				Update();
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//
		// 代码生成
		CString GenCode(DWORD sh /* = PSH_CODE */)
		{
			CString XX_INPUT;
			if (sh == VSH_CODE)
				XX_INPUT = _T("VS_OUTPUT VS_Main(VS_INPUT In)");
			else if (sh == PSH_CODE)
				XX_INPUT = _T("PS_OUTPUT PS_Main(PS_INPUT In) : COLOR");

			return XX_INPUT;
		}

		CString GetStruct(DWORD sh)
		{
			CString XX_INPUT;
			if (sh == VSH_CODE)
				XX_INPUT = _T("struct VS_INPUT {\n");
			else if (sh == PSH_CODE)
				XX_INPUT = _T("struct PS_INPUT {\n");

			// 生成入口函数
			for (int i = 0; i < M_TYPES.size(); ++i)
			{
				XX_INPUT += M_TYPES[i];
				XX_INPUT += _T(' ');
				XX_INPUT += M_NAMES[i];
				XX_INPUT += _T(" : ");
				XX_INPUT += M_SEMANTICS[i];
				XX_INPUT += _T(";\n");
			}

			XX_INPUT += _T("};\n");

			return XX_INPUT;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;

		vector<CString> M_NAMES;
		vector<CString> M_TYPES;
		vector<CString> M_SEMANTICS;
		INT m_count = 0;
	};
}