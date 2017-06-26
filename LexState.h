#pragma once

#include "stdafx.h"

#include "HLSLLexer.h"

class CHLSLLexer;

enum EHLSLLexState
{
	E_NORMAL,
	/////////////////////////////
	E_COMMENT,
	/////////////////////////////
	E_KEYWORD_BEGIN,
	E_FLOAT,
	E_FLOAT2,
	E_FLOAT3,
	E_FLOAT4,
	E_INT,
	E_INT2,
	E_INT3,
	E_INT4,
	E_MAMTRIX,
	E_VECTOR,
	E_SAMPLER,
	E_TEXTURE,
	E_TEXTURE1D,
	E_TEXTURE2D,
	E_TEXTURE3D,
	E_TEXTURECUBE,
	E_SAMPLERSTATE,
	E_STRUCT,
	E_TYPEDEF,
	E_WHILE,
	E_DO,
	E_FOR,
	E_IF,
	E_BOOL,
	E_ELSE,
	E_VSIN,
	E_VSOUT,
	E_PSIN,
	E_PSOUT,
	E_KEYWORDS_END,
	/////////////////////////////
	E_PARAMETERS_BEGIN,
	E_EXTERN,
	E_NOINTERPOLATION,
	E_PRECISE,
	E_SHARED,
	E_GROUPSHARED,
	E_STATIC,
	E_UNIFORM,
	E_VOLATILE,
	E_CONST,
	E_ROWMAJOR,
	E_COLMAJOR,
	E_PARAMETERS_END,
	/////////////////////////////
	E_FUNC_BEGIN,
	E_ABS,
	E_ACOS,
	E_ASIN,
	E_ATAN,
	E_CEIL,
	E_CLAMP,
	E_CLIP,
	E_COS,
	E_CROSS,
	E_DDX,
	E_DDY,
	E_DOTFUNC,
	E_DEGRESS,
	E_DISTANCE,
	E_EXP,
	E_EXP2,
	E_FLOOR,
	E_FMOD,
	E_LENGTH,
	E_LERP,
	E_LIT,
	E_LOG,
	E_LOG10,
	E_LOG2,
	E_MAX,
	E_MIN,
	E_MULFUN,
	E_NOISE,
	E_NORMALIZE,
	E_POW,
	E_RADIANS,
	E_REFLECT,
	E_REFRACT,
	E_ROUND,
	E_SIN,
	E_SQRT,
	E_SATURATE,
	E_TAN,
	E_TEX1D,
	E_TEX2D,
	E_TEX3D,
	E_TEXCUBE,
	E_TRANSPOSE,
	E_FUNC_END,

	/////////////////////////////
	E_ID,
	E_DIGITAL,
	E_STRING,
	/////////////////////////////
	E_SYMBOL_BEGIN,
	E_ASSIGN,  //  =
	E_PLUSASSIGN, // +=
	E_SUBASSIGN,  // -=
	E_MULASSIGN,  // *=
	E_DIVASSIGN,  // /=
	E_NOT,  //  !
	E_POSITIVE,  // +
	E_NEGATIVE,  // -
	E_ADD,  // +
	E_SUB,  // -
	E_MUL,  // *
	E_DIV,  // /
	E_MOD,  // %
	E_BOOLAND, // &&
	E_BOOLOR,  // ||
	E_BOOLLESS,  // <
	E_BOOLGREAT,  // >
	E_BOOLEQUAL,  // ==
	E_BOOLLESSEQ,  // <=
	E_BOOLGREATEEQ,  // >=
	E_BOOLNOTEQUAL, // !=
	E_PLUSPLUS,  // ++
	E_SUBSUB, // --
	E_COMMA,  // ,
	E_LEFTBARCKET,  // [
	E_RIGHTBARCKET,  // ]
	E_LEFTBRACE,  // {
	E_RIGHTBRACE,  // }
	E_RIGHTPAREN,  // )
	E_LEFTPAREN,  // (
	E_SEMIC,	// ;
	E_QUOTE, // "
	E_SINGLEQUOTA, // '
	E_COLON, // :
	E_DOT,  // .
	E_SYMBOL_END,
	/////////////////////////////
	FUNC_COLOR = RGB(200, 100, 255),
	ID_COLOR = RGB(0, 0, 0),
	PARAM_COLOR = RGB(200, 0, 255),
	KEYWORDS_COLOR = RGB(0, 0, 200),
	STRING_COLOR = RGB(200, 100, 0),
	DIGITAL_COLOR = RGB(200, 0, 0),
	COMMENT_COLOR = RGB(0, 255, 0),
};

struct LexStateMap
{
	const WCHAR* _lexeme;
	DWORD _state;
	LexStateMap(const WCHAR* s, DWORD st):_lexeme(s),_state(st){}
};

const  LexStateMap const LexStateMapping[] = 
{
	{ _T("float"), E_FLOAT },
	{ _T("float2"), E_FLOAT2 },
	{ _T("float3"), E_FLOAT3 },
	{ _T("float4"), E_FLOAT4 },

	{ _T("int"), E_INT },
	{ _T("int2"), E_INT2 },
	{ _T("int3"), E_INT3 },
	{ _T("int4"), E_INT4 },

	{ _T("VS_INPUT"), E_VSIN },
	{ _T("VS_OUTPUT"), E_VSOUT },
	{ _T("PS_INPUT"), E_PSIN },
	{ _T("PS_OUTPUT"), E_PSOUT },

	{ _T("float4x4"), E_MAMTRIX },
	{ _T("float3x3"), E_MAMTRIX },
	{ _T("float2x2"), E_MAMTRIX },
	{ _T("float3x4"), E_MAMTRIX },
	{ _T("float2x3"), E_MAMTRIX },
	{ _T("matrix"), E_MAMTRIX },
	{ _T("vector"), E_VECTOR },
	{ _T("sampler"), E_SAMPLER },
	{ _T("sampler_state"), E_SAMPLERSTATE },
	{ _T("typedef"), E_TYPEDEF },
	{ _T("texture"), E_TEXTURE },
	{ _T("Texture1D"), E_TEXTURE1D },
	{ _T("Texture2D"), E_TEXTURE2D },
	{ _T("Texture3D"), E_TEXTURE3D },
	{ _T("TextureCUBE"), E_TEXTURECUBE },
	{ _T("struct"), E_STRUCT },
	{ _T("typedef"), E_TYPEDEF },
	{ _T("if"), E_IF },
	{ _T("else"), E_ELSE },
	{ _T("for"), E_FOR },
	{ _T("do"), E_DO },
	{ _T("while"), E_WHILE },
	{ _T("bool"), E_BOOL },
	/////////////////////////////////////////
	{ _T("abs"), E_ABS },
	{ _T("acos"), E_ACOS },
	{ _T("asin"), E_ASIN },
	{ _T("atan"), E_ATAN },
	{ _T("ceil"), E_CEIL },
	{ _T("clamp"), E_CLAMP },
	{ _T("cos"), E_COS },
	{ _T("cross"), E_CROSS },
	{ _T("ddx"), E_DDX },
	{ _T("ddy"), E_DDY },
	{ _T("dot"), E_DOTFUNC },
	{ _T("degrees"), E_DEGRESS },
	{ _T("distance"), E_DISTANCE },
	{ _T("exp"), E_EXP },
	{ _T("exp2"), E_EXP2 },
	{ _T("floor"), E_FLOOR },
	{ _T("fmod"), E_FMOD },
	{ _T("length"), E_LENGTH },
	{ _T("lerp"), E_LERP },
	{ _T("lit"), E_LIT },
	{ _T("log"), E_LOG },
	{ _T("log2"), E_LOG2 },
	{ _T("log10"), E_LOG10 },
	{ _T("max"), E_MAX },
	{ _T("min"), E_MIN },
	{ _T("mul"), E_MULFUN },
	{ _T("noise"), E_NOISE },
	{ _T("normalize"), E_NORMALIZE },
	{ _T("pow"), E_POW },
	{ _T("radians"), E_RADIANS },
	{ _T("reflect"), E_REFLECT },
	{ _T("refract"), E_REFRACT },
	{ _T("round"), E_ROUND },
	{ _T("sin"), E_SIN },
	{ _T("sqrt"), E_SQRT },
	{ _T("tan"), E_TAN },
	{ _T("saturate"), E_SATURATE },
	{ _T("tex1d"), E_TEX1D },
	{ _T("tex2d"), E_TEX2D },
	{ _T("tex3d"), E_TEX3D },
	{ _T("texCUBE"), E_TEXCUBE },
	{ _T("transpose"), E_TRANSPOSE },
	//////////////////////////////////////////
	{ _T("="), E_ASSIGN },
	{ _T("+="), E_PLUSASSIGN },
	{ _T("-="), E_SUBASSIGN },
	{ _T("*="), E_MULASSIGN },
	{ _T("/="), E_DIVASSIGN },
	{ _T("+"), E_ADD },
	{ _T("-"), E_SUB },
	{ _T("*"), E_MUL },
	{ _T("/"), E_DIV },
	{ _T("++"), E_PLUSPLUS },
	{ _T("--"), E_SUBSUB },
	{ _T("%"), E_MOD },
	{ _T(">"), E_BOOLGREAT },
	{ _T("<"), E_BOOLLESS },
	{ _T(">="), E_BOOLGREATEEQ },
	{ _T("<="), E_BOOLLESSEQ },
	{ _T("!="), E_BOOLNOTEQUAL },
	{ _T("&&"), E_BOOLAND },
	{ _T("||"), E_BOOLOR },
	{ _T("!"), E_NOT },
	{ _T(","), E_COMMA },
	{ _T("["), E_LEFTBARCKET },
	{ _T("]"), E_RIGHTBARCKET },
	{ _T("{"), E_LEFTBRACE },
	{ _T("}"), E_RIGHTBRACE },
	{ _T("("), E_LEFTPAREN },
	{ _T(")"), E_RIGHTPAREN },
	{ _T(";"), E_SEMIC },
	{ _T("\""), E_QUOTE },
	{ _T("'"), E_SINGLEQUOTA },
	{ _T(":"), E_COLON },
	{ _T("."), E_DOT },
	///////////////////////////////////////////
	{ _T("extern"), E_EXTERN },
	{ _T("static"), E_STATIC },
	{ _T("uniform"), E_UNIFORM },
	{ _T("const"), E_CONST },
	{ _T("nointerpolation"), E_NOINTERPOLATION },
	{ _T("precise"), E_PRECISE },
	{ _T("shared"), E_SHARED },
	{ _T("volatile"), E_VOLATILE },
	{ _T("row_major"), E_ROWMAJOR },
	{ _T("column_major"), E_COLMAJOR },
	{ _T("groupshared"), E_GROUPSHARED }
};

enum STATE_INDEX
{
	STATE_NORMAL,
	STATE_MULTICOMMENT,
	STATE_LINECOMMENT,
	STATE_ASSIGN,
	STATE_EQUAL,
	STATE_ADD,
	STATE_SUB,
	STATE_MUL,
	STATE_DIV,
	STATE_NOT,
	STATE_NOTEQUAL,
	STATE_LESS,
	STATE_GREAT,
	STATE_LESSEQUAL,
	STATE_GREATEEQUAL,
	STATE_MOD,
	STATE_COMMA,
	STATE_LEFTBRACKET,
	STATE_RIGHTBRACKET,
	STATE_LEFTBRACE,
	STATE_RIGHTBRACE,
	STATE_LEFTPAREN,
	STATE_RIGHTPAREN,
	STATE_SEMIC,
	STATE_SINGLEQUOT,
	STATE_QUOT,
	STATE_PLUSASSIGN,
	STATE_SUBASSIGN,
	STATE_MULASSIGN,
	STATE_DIVASSIGN,
	STATE_PLUSPLUS,
	STATE_SUBSUB,
	STATE_AND,
	STATE_OR,
	STATE_ID,
	STATE_DIGITAL,
	STATE_STRING,
	STATE_DOT,
	STATE_COLON
};

//////////////////////////////////////////////////////////////////////////
//
// lexer的状态实际上分两大类， 一类是操作符，一类是关键字。
// 在分析过程中状态机被分为两层，最上面一层按照 注释、操作符、关键字\内置函数名分类，第二层将关键词与内置函数名分类
// 相对于关键字来讲， 操作符的类型与种类是比较固定的，因此放在第一层进行分析。

class ILexState
{
public:
	ILexState() {}
	virtual ~ILexState() {}
	DWORD _STATE;
	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme) = 0;
	virtual bool IsState(DWORD s) { return _STATE == s; }
};

class Lexer
{
public:
	static bool isAlpha(WCHAR c)
	{
		return ((c >= _T('a') && c <= _T('z')) || (c >= _T('A') && c <= _T('Z')));
	}

	static bool isUpperAlpha(WCHAR c)
	{
		return (c >= _T('A') && c <= _T('Z'));
	}

	static bool isLowerAlpha(WCHAR c)
	{
		return (c >= _T('A') && c <= _T('Z'));
	}

	static bool isDigital(WCHAR c)
	{
		return (c >= _T('0') && c <= _T('9'));
	}
};

class LexNormalState : public ILexState
{
public:
	LexNormalState() { _STATE = E_NORMAL; }
	virtual ~LexNormalState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLineCommentState : public ILexState
{
public:
	LexLineCommentState() { _STATE = E_COMMENT; }
	virtual ~LexLineCommentState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexMulLineCommentState : public ILexState
{
public:
	LexMulLineCommentState() { _STATE = E_COMMENT; }
	virtual ~LexMulLineCommentState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexColonState : public ILexState
{
public:
	LexColonState() { _STATE = E_COLON; }
	virtual ~LexColonState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexDotState : public ILexState
{
public:
	LexDotState() { _STATE = E_COLON; }
	virtual ~LexDotState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexAssignState : public ILexState
{
public:
	LexAssignState() { _STATE = E_ASSIGN; }
	virtual ~LexAssignState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexAndState : public ILexState
{
public:
	LexAndState() { _STATE = E_BOOLAND; }
	virtual ~LexAndState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexOrState : public ILexState
{
public:
	LexOrState() { _STATE = E_BOOLOR; }
	virtual ~LexOrState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexEqualState : public ILexState
{
public:
	LexEqualState() { _STATE = E_BOOLEQUAL; }
	virtual ~LexEqualState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexAddState : public ILexState
{
public:
	LexAddState() { _STATE = E_ADD; }
	virtual ~LexAddState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexPlusPlusState : public ILexState
{
public:
	LexPlusPlusState() { _STATE = E_PLUSPLUS; }
	virtual ~LexPlusPlusState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexSubState : public ILexState
{
public:
	LexSubState() { _STATE = E_SUB; }
	virtual ~LexSubState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexSubSubState : public ILexState
{
public:
	LexSubSubState() { _STATE = E_SUBSUB; }
	virtual ~LexSubSubState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexMulState : public ILexState
{
public:
	LexMulState() { _STATE = E_MUL; }
	virtual ~LexMulState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexDivState : public ILexState
{
public:
	LexDivState() { _STATE = E_DIV; }
	virtual ~LexDivState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexNotState : public ILexState
{
public:
	LexNotState() { _STATE = E_NOT; }
	virtual ~LexNotState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexNotEqualState : public ILexState
{
public:
	LexNotEqualState() { _STATE = E_BOOLNOTEQUAL; }
	virtual ~LexNotEqualState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLessState : public ILexState
{
public:
	LexLessState() { _STATE = E_BOOLLESS; }
	virtual ~LexLessState() {}


	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexGreaterState : public ILexState
{
public:
	LexGreaterState() { _STATE = E_BOOLGREAT; }
	virtual ~LexGreaterState() {}


	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLessEqualState : public ILexState
{
public:
	LexLessEqualState() { _STATE = E_BOOLLESSEQ; }
	virtual ~LexLessEqualState() {}


	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexCommaState : public ILexState
{
public:
	LexCommaState() { _STATE = E_COMMA; }
	virtual ~LexCommaState() {}


	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLeftBracketState : public ILexState
{
public:
	LexLeftBracketState() { _STATE = E_LEFTBARCKET; }
	virtual ~LexLeftBracketState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexRightBracketState : public ILexState
{
public:
	LexRightBracketState() { _STATE = E_RIGHTBARCKET; }
	virtual ~LexRightBracketState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLeftBraceState : public ILexState
{
public:
	LexLeftBraceState() { _STATE = E_LEFTBRACE; }
	virtual ~LexLeftBraceState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexRightBraceState : public ILexState
{
public:
	LexRightBraceState() { _STATE = E_RIGHTBRACE; }
	virtual ~LexRightBraceState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexLeftParenState : public ILexState
{
public:
	LexLeftParenState() { _STATE = E_LEFTPAREN; }
	virtual ~LexLeftParenState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexRightParenState : public ILexState
{
public:
	LexRightParenState() { _STATE = E_RIGHTPAREN; }
	virtual ~LexRightParenState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexSemicState : public ILexState
{
public:
	LexSemicState() { _STATE = E_SEMIC; }
	virtual ~LexSemicState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexSingleQuotState : public ILexState
{
public:
	LexSingleQuotState() { _STATE = E_SINGLEQUOTA; }
	virtual ~LexSingleQuotState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexQuotState : public ILexState
{
public:
	LexQuotState() { _STATE = E_QUOTE; }
	virtual ~LexQuotState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexGreaterEqualState : public ILexState
{
public:
	LexGreaterEqualState() { _STATE = E_BOOLGREATEEQ; }
	virtual ~LexGreaterEqualState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};


class LexModState : public ILexState
{
public:
	LexModState() { _STATE = E_MOD; }
	virtual ~LexModState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexPlusAssignState : public ILexState
{
public:
	LexPlusAssignState() { _STATE = E_PLUSASSIGN; }
	virtual ~LexPlusAssignState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexSubAssignState : public ILexState
{
public:
	LexSubAssignState() { _STATE = E_SUBASSIGN; }
	virtual ~LexSubAssignState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexMulAssignState : public ILexState
{
public:
	LexMulAssignState() { _STATE = E_MULASSIGN; }
	virtual ~LexMulAssignState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexDivAssignState : public ILexState
{
public:
	LexDivAssignState() { _STATE = E_DIVASSIGN; }
	virtual ~LexDivAssignState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexIDState : public ILexState
{
public:
	LexIDState() { _STATE = E_ID; }
	virtual ~LexIDState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexDigitalState : public ILexState
{
public:
	LexDigitalState() { _STATE = E_DIGITAL; }
	virtual ~LexDigitalState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};

class LexStringState : public ILexState
{
public:
	LexStringState() { _STATE = E_STRING; }
	virtual ~LexStringState() {}

	virtual ILexState* CheckCondition(DWORD& index, DWORD end, CString& code, CString& lexeme);
};