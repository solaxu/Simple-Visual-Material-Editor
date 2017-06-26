#pragma once

#include <vector>
#include "LexState.h"

using std::vector;

class ILexState;

struct SHLSLToken
{
	SHLSLToken():_begin(0),_end(0),_color(0),_type(0)
	{

	}
	DWORD _color;
	CString _lexeme;
	DWORD _begin, _end;
	DWORD _type;
};

struct STrieNode
{
	WCHAR _c;
	DWORD _type;
	STrieNode* _links[128];
	STrieNode() : _c(_T('\0')), _type(0)
	{
		for (int i = 0; i < 128; ++i)
			_links[i] = NULL;
	}
};

class CHLSLLexer
{
public:
	static vector<ILexState*> STATES;
	static CHLSLLexer* _Lexer;
public:
	CHLSLLexer();
	~CHLSLLexer();

public:
	CString m_code;
	STrieNode m_tree;

	vector<SHLSLToken> m_tokenStream;

	void LexRange(DWORD begin, DWORD end);

	DWORD GetTokenColor(DWORD type);

	DWORD GetTokenType(CString& s);

	void BuildDict();
};

