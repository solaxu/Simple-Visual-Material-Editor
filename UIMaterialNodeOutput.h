#pragma once

#include "UI.h"
#include "UIMgr.h"
#include "InoutputDlg.h"
#include <vector>

using std::vector;

namespace ShaderEditor
{
	class UINodeOutput : public SUIWindow
	{
	public:
		UINodeOutput(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Output"));
			m_nodeType->ShowBorder(TRUE);

			isStruct = TRUE;
		}

		virtual ~UINodeOutput()
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
			m_nodeType->Name = CString(_T("Output"));
			m_nodeType->ShowBorder(TRUE);

			float OutY = Top + Height * 2 + 5;

			for (int i = 0; i < m_count; ++i)
			{
				CString s;
				s.Format(_T("%s:%s"), M_TYPES[i], M_SEMANTICS[i]);
				SUILabel* label = new SUILabel(Left, Top + Height * (2 + i), Width, Height, UIDrawParams::DefaultBorderWidth, this);
				label->ShowBorder(TRUE);
				label->Name = s;

				SUIButton* OutputX = new SUIButton(Left + Width, OutY, 40, 20, 2, this);
				OutY += 30;
				OutputX->Name = M_NAMES[i];
				OutputX->ID = UIMgr::GenerateUIID();
				OutputX->Usage = SUIButton::LINK_IN;
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

		CString GetStruct(DWORD sh)
		{
			CString XX_INPUT;
			if (sh == VSH_CODE)
				XX_INPUT = _T("\nstruct VS_OUTPUT {\n");
			else if (sh == PSH_CODE)
				XX_INPUT = _T("\nstruct PS_OUTPUT {\n");

			CString str;

			// 生成结构体
			for (int i = 0; i < M_TYPES.size(); ++i)
			{
				str += M_TYPES[i];
				str += _T(' ');
				str += M_NAMES[i];
				str += _T(" : ");
				str += M_SEMANTICS[i];
				str += _T(";\n");
			}

			str += _T("};\n");

			return XX_INPUT + str;
		}

		CString SyntaxTreeGenCode(DWORD sh /* = PSH_CODE */)
		{
			CString str;
			vector<CString> inStrs;
			for each (auto ptr in M_INPUTS)
			{
				auto wnd = dynamic_cast<SUIWindow*>(ptr->Parent);
				auto btn = dynamic_cast<SUIButton*>(ptr);
				// 接入的那个点
				if (btn && btn->IN_BTN.size() == 1)
					btn = btn->IN_BTN[0];
				auto IN_WND = dynamic_cast<SUIWindow*>(btn->Parent);
				if (IN_WND)
				{
					if (IN_WND->M_VISITED == FALSE)
					{
						IN_WND->M_VISITED = TRUE;
						str += IN_WND->SyntaxTreeGenCode(sh);
					}
					
					if (IN_WND->isStruct)
					{
						CString inStr = IN_WND->Name;
						inStr += _T(".");
						inStr += btn->Name;
						inStr += _T(";\n");
						inStrs.push_back(inStr);
					}
					else
					{
						CString inStr;
						inStr.Format(_T("%s;\n"), IN_WND->Name);
						inStrs.push_back(inStr);
					}
				}
			}

			int i = 0;
			for each (auto ptr in M_INPUTS)
			{
				CString s = Name + _T(".");
				auto btn = dynamic_cast<SUIButton*>(ptr);
				// 接入的那个点
				if (btn && btn->IN_BTN.size() == 1)
				{
					s += btn->Name;
					s += _T(" = ");
					s += inStrs[i];
				}
				str += s;
				++ i;
			}

			str += _T("\n");
			return str;
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