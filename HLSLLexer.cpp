#include "stdafx.h"
#include "LexState.h"

//////////////////////////////////////////////////////////////////////////

CHLSLLexer* CHLSLLexer::_Lexer = new CHLSLLexer;

vector<ILexState*> CHLSLLexer::STATES = {
	new LexNormalState(),
	new LexMulLineCommentState(),
	new LexLineCommentState(),
	new LexAssignState(),
	new LexEqualState,
	new LexAddState(),
	new LexSubState(),
	new LexMulState(),
	new LexDivState(),
	new LexNotState(),
	new LexNotEqualState(),
	new LexLessState(),
	new LexGreaterState(),
	new LexLessEqualState(),
	new LexGreaterEqualState(),
	new LexModState(),
	new LexCommaState(),
	new LexLeftBracketState(),
	new LexRightBracketState(),
	new LexLeftBraceState(),
	new LexRightBraceState(),
	new LexLeftParenState(),
	new LexRightParenState(),
	new LexSemicState(),
	new LexSingleQuotState(),
	new LexQuotState(),
	new LexPlusAssignState(),
	new LexSubAssignState(),
	new LexMulAssignState(),
	new LexDivAssignState(),
	new LexPlusPlusState(),
	new LexSubSubState(),
	new LexAndState(),
	new LexOrState(),
	new LexIDState(),
	new LexDigitalState(),
	new LexStringState(),
	new LexDotState(),
	new LexColonState()
};

CHLSLLexer::CHLSLLexer()
{
	BuildDict();
}


CHLSLLexer::~CHLSLLexer()
{
}


void CHLSLLexer::LexRange(DWORD begin, DWORD end)
{
	if (begin > m_code.GetLength())
		begin = m_code.GetLength() - 1;
	if (end > m_code.GetLength())
		end = m_code.GetLength() - 1;

	m_tokenStream.clear();

	DWORD index = begin;
	LexNormalState normalState;
	ILexState* LEX_STATE = CHLSLLexer::STATES[E_NORMAL];
	CString lexeme;
	DWORD preState = 0;
	while (index <= end)
	{
		preState = LEX_STATE->_STATE;
		LEX_STATE = LEX_STATE->CheckCondition(index, end, m_code, lexeme);

		if (LEX_STATE->IsState(EHLSLLexState::E_NORMAL) && lexeme.GetLength() != 0)
		{
			SHLSLToken token;
			token._type = GetTokenType(lexeme);
			if (token._type == E_NORMAL)
				token._type = preState;
			token._end = index;
			token._begin = index - lexeme.GetLength();
			token._lexeme = lexeme;
			token._color = GetTokenColor(token._type);
			m_tokenStream.push_back(token);
			lexeme = _T("");
		}
	}
	return;
}

DWORD CHLSLLexer::GetTokenColor(DWORD type)
{
	if (type == E_ID)
		return ID_COLOR;
	if (type > E_FUNC_BEGIN && type < E_FUNC_END)
		return FUNC_COLOR;
	if (type > E_KEYWORD_BEGIN && type < E_KEYWORDS_END)
		return KEYWORDS_COLOR;
	if (type == E_COMMENT)
		return COMMENT_COLOR;
	if (type == E_DIGITAL)
		return DIGITAL_COLOR;
	if (type == E_STRING)
		return STRING_COLOR;
	if (type > E_PARAMETERS_BEGIN && type < E_PARAMETERS_END)
		return PARAM_COLOR;
	return 0;
}

DWORD CHLSLLexer::GetTokenType(CString& s)
{
	if (s.GetLength() == 0)
		return E_NORMAL;
	DWORD index = 0;
	auto root = &m_tree;
	while (TRUE)
	{
		DWORD linkIndex = s[index] - _T('\0');
		root = root->_links[linkIndex];
		if (root == NULL)
		{
				break;
		}
		else
		{
			if (index == s.GetLength() - 1)
			{
				return root->_type;
			}
		}
		++index;
	}
	return E_NORMAL;
}

void CHLSLLexer::BuildDict()
{
	STrieNode* root = &m_tree;
	for (int i = 0; i < 109; ++i)
	{
		const CString& s = LexStateMapping[i]._lexeme;
		DWORD index = 0;
		while (index < s.GetLength())
		{
			DWORD linkIndex = s[index] - _T('\0');
			if (root->_links[linkIndex] == NULL)
			{
				STrieNode* ptr = new STrieNode();
				root->_links[linkIndex] = ptr;
				ptr->_c = s[index];
				root = ptr;
			}
			else
			{
				root = root->_links[linkIndex];
			}
			++index;
			if (s.GetLength() == index)
				root->_type = LexStateMapping[i]._state;
		}
		root = &m_tree;
	}
}