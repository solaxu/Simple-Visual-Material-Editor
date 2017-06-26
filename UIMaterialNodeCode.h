#pragma once

#include "UI.h"
#include "UIMgr.h"
#include "CodeNodeDlg.h"
#include "HLSLLexer.h"
#include <vector>

using std::vector;

namespace ShaderEditor
{
	class UINodeCode : public SUIWindow
	{
	public:
		UINodeCode(float x, float y, float width, float heigth, UIObject* parent)
			: SUIWindow(x, y, width, heigth, UIDrawParams::DefaultBorderWidth, parent)
		{
			m_nodeType = new SUILabel(x, y + heigth, width, heigth, UIDrawParams::DefaultBorderWidth, this);
			m_nodeType->Name = CString(_T("Code"));
			m_nodeType->ShowBorder(TRUE);
		}

		virtual ~UINodeCode()
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
			Name = m_nodeType->Name;
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
			m_nodeType->Name = CString(_T("Code"));
			m_nodeType->ShowBorder(TRUE);

			float OutY = Top + Height * 2 + 5;
			float InY = OutY;
			// lex first
			CHLSLLexer::_Lexer->m_code = m_code;
			CHLSLLexer::_Lexer->LexRange(0, m_code.GetLength());
			ParseFunctions(CHLSLLexer::_Lexer->m_tokenStream);

			DWORD count = M_TYPES.size();

			for (int i = 0; i < count; ++i)
			{
				CString s;
				s.Format(_T("in : %s"), M_TYPES[i]);
				SUILabel* label = new SUILabel(Left, Top + Height * (2 + i), Width, Height, UIDrawParams::DefaultBorderWidth, this);
				label->ShowBorder(TRUE);
				label->Name = s;

				SUIButton* OutputX = new SUIButton(Left + Width, OutY, 40, 20, 2, this);
				OutY += 30;
				OutputX->Name = CString(_T(""));
				OutputX->ID = UIMgr::GenerateUIID();
				OutputX->Usage = SUIButton::LINK_IN;
			}

			CString s;
			s.Format(_T("out : %s"), M_OUT);
			SUILabel* label = new SUILabel(Left, Top + Height * (2 + count), Width, Height, UIDrawParams::DefaultBorderWidth, this);
			label->ShowBorder(TRUE);
			label->Name = s;

			SUIButton* OutputX = new SUIButton(Left - 40, InY, 40, 20, 2, this);
			OutputX->Name = CString(_T(""));
			OutputX->ID = UIMgr::GenerateUIID();
			OutputX->Usage = SUIButton::LINK_OUT;

		}

		void EditObject()
		{
			CCodeNodeDlg dlg;
			dlg.m_code = m_code;

			if (IDOK == dlg.DoModal())
			{
				m_code = dlg.m_code;
				Update();
			}
		}

		void ParseFunctions(std::vector<SHLSLToken>& stream)
		{
			m_funs.clear();
			M_NAMES.clear();
			M_TYPES.clear();
			// 创建一个func
			FuncBlock fblock;
			int i = 0;
			bool infunc = FALSE;
			bool inParams = FALSE;
			bool inBody = FALSE;
			for (; i < stream.size();)
			{
				if (infunc)
				{
					if (inParams)
					{
						if (stream[i]._type == E_RIGHTPAREN)
						{
							++i;
							inParams = FALSE;
						}
						else
						{
							if (stream[i]._type == E_ID)
							{
								fblock.m_papams.push_back(&stream[i]);
								++i;
							}
							else if (stream[i]._type >= E_KEYWORD_BEGIN && stream[i]._type <= E_KEYWORDS_END)
							{
								fblock.m_paramTypes.push_back(&stream[i]);
								++i;
							}
							else if (stream[i]._type == E_COMMA)
							{
								++i;
							}
							else
							{
								++i;
							}
						}
					}
					else if (stream[i]._type == E_LEFTBRACE)
					{
						inBody = TRUE;
						++i;
					}
					else if (inBody)
					{
						if (stream[i]._type == E_RIGHTBRACE)
						{
							inBody = FALSE;
							infunc = FALSE;
							m_funs.push_back(fblock);
							++i;
						}
						else
						{
							if (stream[i]._type == E_ID)
								fblock.m_ids.push_back(&stream[i]);
							++i;
						}
					}
					else
					{
						++i;
					}
				}
				else if (stream[i]._type >= E_KEYWORD_BEGIN && stream[i]._type <= E_KEYWORDS_END)
				{
					// 向前看2个tokens
					if (stream[i + 1]._type == E_ID && stream[i + 2]._type == E_LEFTPAREN)
					{
						if (infunc == FALSE)
						{
							fblock.m_caller.clear();
							fblock.m_ids.clear();
							fblock.m_papams.clear();
							fblock.m_paramTypes.clear();
							fblock.m_ret = NULL;
							fblock.m_tk = NULL;

							fblock.m_tk = &stream[i + 1];
							fblock.m_ret = &stream[i];
							i += 3;
							infunc = TRUE;
							inParams = TRUE;
						}
					}
				}
				else
				{
					++i;
				}
			}

			// 建立函数之间的调用关系

			// ToDo
			for (int i = 0; i < m_funs.size(); ++i)
			{
				for (int j = 0; j < m_funs.size(); ++j)
				{
					for (auto id : m_funs[j].m_ids)
					{
						if (m_funs[i].m_tk->_lexeme == id->_lexeme)
						{
							m_funs[i].m_caller.push_back(&m_funs[j]);
						}
					}
				}
			}

			// 只有最外层的函数没有被调用
			DWORD index = 0;
			for (auto fun : m_funs)
			{
				if (fun.m_caller.size() == 0)
				{
					break;
				}
				++index;
			}

			for (auto ptr : m_funs[index].m_papams)
			{
				M_NAMES.push_back(ptr->_lexeme);
			}

			for (auto ptr : m_funs[index].m_paramTypes)
			{
				M_TYPES.push_back(ptr->_lexeme);
			}

			M_OUT = m_funs[index].m_ret->_lexeme;
			M_FUN_NAME = m_funs[index].m_tk->_lexeme;
		}

		virtual CString SyntaxTreeGenCode(DWORD sh /* = PSH_CODE */)
		{
			CString s;

			CString str = M_OUT;
			str += _T(" ");
			str += m_nodeType->Name;
			str += _T(" = ");
			str += M_FUN_NAME;
			str += _T("(");

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

				if (i < M_INPUTS.size())
					str += _T(",");
			}
			str += _T(");\n");

			return s + str;
		}

	public:
		SUILabel* m_nodeType = NULL;
		SUILabel* m_body = NULL;
		vector<CString> M_NAMES;
		vector<CString> M_TYPES;
		vector<FuncBlock> m_funs;
		CString M_OUT;
		CString M_FUN_NAME;
		CString m_code;
	};
}