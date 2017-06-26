#include "stdafx.h"
#include "LexState.h"

ILexState* LexNormalState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T(' ') || code[index] == _T('\n') ||
		code[index] == _T('\0') || code[index] == _T('\r'))
	{
		++index;
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else if (Lexer::isAlpha(code[index]) || code[index] == _T('_'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_ID];
	}
	else if (Lexer::isAlpha(code[index]) || code[index] == _T('<'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LESS];
	}
	else if (Lexer::isAlpha(code[index]) || code[index] == _T('>'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_GREAT];
	}
	else if (Lexer::isDigital(code[index]) || code[index] == _T('.'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_DIGITAL];
	}
	else if (code[index] == _T('"'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_STRING];
	}
	else if (code[index] == _T('+'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_ADD];
	}
	else if (code[index] == _T('-'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_SUB];
	}
	else if (code[index] == _T('*'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MUL];
	}
	else if (code[index] == _T('/'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_DIV];
	}
	else if (code[index] == _T('&'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_AND];
	}
	else if (code[index] == _T('|'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_OR];
	}
	else if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_ASSIGN];
	}
	else if (code[index] == _T(','))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_COMMA];
	}
	else if (code[index] == _T(';'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_SEMIC];
	}
	else if (code[index] == _T('{'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LEFTBRACE];
	}
	else if (code[index] == _T('}'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_RIGHTBRACE];
	}
	else if (code[index] == _T('['))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LEFTBRACKET];
	}
	else if (code[index] == _T(']'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_RIGHTBRACKET];
	}
	else if (code[index] == _T('('))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LEFTPAREN];
	}
	else if (code[index] == _T(')'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_RIGHTPAREN];
	}
	else if (code[index] == _T('\''))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_SINGLEQUOT];
	}
	else if (code[index] == _T('"'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_QUOT];
	}
	else if (code[index] == _T('%'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MOD];
	}
	else if (code[index] == _T('.'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_DOT];
	}
	else if (code[index] == _T(':'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MOD];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_ID];
	}

	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexLineCommentState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('\n') || code[index] == _T('\r') || code[index] == _T('\0'))
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LINECOMMENT];
	}
}

ILexState* LexMulLineCommentState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index >= end)
		return CHLSLLexer::STATES[STATE_NORMAL];
//	lexeme += code[index++];

	if (code[index - 1] == _T('*') && code[index] == _T('/'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MULTICOMMENT];
	}
}

ILexState* LexAssignState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_EQUAL];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexAndState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('&'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_AND];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexOrState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('|'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_OR];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexEqualState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexAddState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_PLUSASSIGN];
	}
	else if (code[index] == _T('+'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_PLUSPLUS];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexPlusPlusState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexSubState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_SUBASSIGN];
	}
	else if (code[index] == _T('-'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_SUBSUB];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexSubSubState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexMulState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MULASSIGN];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexDivState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_DIVASSIGN];
	}
	else if (code[index] == _T('/'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LINECOMMENT];
	}
	else if (code[index] == _T('*'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_MULTICOMMENT];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexNotState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_NOTEQUAL];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexNotEqualState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexLessState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_LESSEQUAL];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexGreaterState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('='))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_GREATEEQUAL];
	}
	else
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
}

ILexState* LexLessEqualState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexCommaState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexLeftBracketState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexRightBracketState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexLeftBraceState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexRightBraceState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexLeftParenState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexRightParenState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexSemicState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexSingleQuotState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexQuotState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexDotState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_DOT];
	return CHLSLLexer::STATES[STATE_DOT];
}

ILexState* LexColonState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_COLON];
	return CHLSLLexer::STATES[STATE_COLON];
}

ILexState* LexGreaterEqualState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexModState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexPlusAssignState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexSubAssignState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexMulAssignState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexDivAssignState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	return CHLSLLexer::STATES[STATE_NORMAL];
}

ILexState* LexIDState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (
		!(
			Lexer::isAlpha(code[index]) ||
			Lexer::isDigital(code[index]) ||
			code[index] == _T('_')
			)
		)
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_ID];
	}
}

ILexState* LexDigitalState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (
		!(
			Lexer::isDigital(code[index]) ||
			code[index] == _T('.')
			)
		)
	{
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_DIGITAL];
	}
}

ILexState* LexStringState::CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme)
{
	if (index > end)
		return CHLSLLexer::STATES[STATE_NORMAL];
	if (code[index] == _T('"'))
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_NORMAL];
	}
	else
	{
		lexeme += code[index++];
		return CHLSLLexer::STATES[STATE_STRING];
	}
}