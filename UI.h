#pragma once

#include "Ulit.h"
#include <vector>
#include <map>
#include <functional>
#include "UIMgr.h"

#define IDC_ALPHABLEND_EANBLE_COMBOX 2001
#define IDC_ALPHABLEND_FUNC_COMBOX 2002
#define IDC_ALPHATEST_ENABLE_COMBOX 2003
#define IDC_BLEND_OP_COMBOX 2004
#define IDC_DESTBLEND_COMBOX 2005
#define IDC_FILLMODE_COMBOX 2006
#define IDC_SHADEMODE_COMBOX 2007
#define IDC_SRCBLEND_COMBOX 2008
#define IDC_ZENABLE_COMBOX 2009
#define IDC_ZFUNC_COMBOX 2010
#define IDC_ZWRITE_COMBOX 2011
#define IDC_ALPHA_REF_COMBOX 2012

namespace ShaderEditor
{
	struct SRenderState
	{
		CString _AlphaBlendEnable;
		CString _AlphaFunc;
		CString _AlphaRef;
		CString _AlphaTestEnalbe;
		CString _BlendOp;
		CString _DestBlend;
		CString _FillMode;
		CString _ShadeMode;
		CString _SrcBlend;
		CString _ZEnable;
		CString _ZFunc;
		CString _ZWritEnable;
		CString _pshVersion;
		CString _vshVersion;

		SRenderState& operator=(const SRenderState& r)
		{
			if (&r != this)
			{
				_AlphaBlendEnable = r._AlphaBlendEnable;
				_AlphaFunc = r._AlphaFunc;
				_AlphaRef = r._AlphaRef;
				_AlphaTestEnalbe = r._AlphaTestEnalbe;
				_BlendOp = r._BlendOp;
				_DestBlend = r._DestBlend;
				_FillMode = r._FillMode;
				_ShadeMode = r._ShadeMode;
				_SrcBlend = r._SrcBlend;
				_ZEnable = r._ZEnable;
				_ZFunc = r._ZFunc;
				_ZWritEnable = r._ZWritEnable;
				_vshVersion = r._vshVersion;
				_pshVersion = r._pshVersion;
			}
			return *this;
		}
	};

	const CString const VSHVersion[] = 
	{
		_T("vs_2_0"),
		_T("vs_3_0"),
		_T("vs_4_0")
	};

	const CString const PSHVersion[] =
	{
		_T("ps_2_0"),
		_T("ps_3_0"),
		_T("ps_4_0")
	};

	const CString const booleanStr[] =
	{
		_T("TRUE"),_T("FALSE")
	};

	const CString const AlphaFuncStr[] =
	{
		_T("Always"),
		_T("Never"),
		_T("Less"),
		_T("Equal"),
		_T("LessEqual"),
		_T("Greater"),
		_T("GreaterEqual"),
		_T("NotEqual")
	};

	const CString const BlendOpStr[] =
	{
		_T("Add"),
		_T("Subtract"),
		_T("RevSubTract"),
		_T("Min"),
		_T("Max")
	};

	const CString const DestBlend[] =
	{
		_T("Zero"),
		_T("One"),
		_T("SrcColor"),
		_T("InvSrcColor"),
		_T("InvSrcAlpha"),
		_T("DestAlpha"),
		_T("DestColor"),
		_T("InvDestColor"),
		_T("SrcAlphaSat"),
		_T("BothSrcAlpha"),
		_T("BothInvSrcAlpha"),
		_T("BlendFactor"),
		_T("InvBlendFactor")
	};

	const CString const FillModeStr[] =
	{
		_T("Point"),
		_T("WireFrame"),
		_T("Solid")
	};

	const CString const ShadeMode[] =
	{
		_T("Flat"),
		_T("Gouraud"),
		_T("Phong")
	};

	const CString const SrcBlendStr[] =
	{
		_T("Zero"),
		_T("One"),
		_T("SrcColor"),
		_T("InvSrcColor"),
		_T("InvSrcAlpha"),
		_T("DestAlpha"),
		_T("InvDestAlpha"),
		_T("DestColor"),
		_T("InvDestColor"),
		_T("SrcAlphaSat"),
		_T("BothSrcAlpha"),
		_T("BothInvSrcAlpha"),
		_T("BlendFactor"),
		_T("InvBlendFactor")
	};

	enum CODE_GEN
	{
		VSH_CODE,
		PSH_CODE
	};

	const CString const FloatTypes[4] =
	{
		_T("float"),
		_T("float2"),
		_T("float3"),
		_T("float4")
	};

	const CString const Semantics[34] = 
	{
		_T("POSITION"),
		_T("COLOR"),
		_T("POSITION0"),
		_T("POSITION1"),
		_T("POSITION2"),
		_T("POSITION3"),
		_T("NORMAL0"),
		_T("NORMAL1"),
		_T("NORMAL2"),
		_T("NORMAL3"),
		_T("TANGENT0"),
		_T("TANGENT1"),
		_T("TANGENT2"),
		_T("TANGENT3"),
		_T("COLOR0"),
		_T("COLOR1"),
		_T("COLOR2"),
		_T("COLOR3"),
		_T("TEXCOORD0"),
		_T("TEXCOORD1"),
		_T("TEXCOORD2"),
		_T("TEXCOORD3"),
		_T("BLENDINDICES0"),
		_T("BLENDINDICES1"),
		_T("BLENDINDICES2"),
		_T("BLENDINDICES3"),
		_T("BLENDWEIGHT0"),
		_T("BLENDWEIGHT1"),
		_T("BLENDWEIGHT2"),
		_T("BLENDWEIGHT3"),
		_T("PSIZE0"),
		_T("PSIZE1"),
		_T("PSIZE2"),
		_T("PSIZE3"),
	};

	struct SSamplerState
	{
		CString		addressU;
		CString		addressV;
		CString		addressW;
		CString		borderColor;
		CString		magFilter;
//		CString		maxAnisotropy; // 默认值
		CString		maxMipLevel;
		CString		minFilter;
		CString		mipFilter;
//		CString		mipMapLodBias; // 默认值
//		CString		sRGBTexture; // 默认值
	};

	inline DWORD MakeColor(DWORD a, DWORD r, DWORD g, DWORD b)
	{
		DWORD c = 0;
		c += ((a & 0xff) << 24);
		c += ((r & 0xff) << 16);
		c += ((g & 0xff) << 8);
		c += (b & 0xff);
		return c;
	}

	const CString const TextureAddress[6] = 
	{
		_T("WRAP"),
		_T("MIRROR"),
		_T("CLAMP"),
		_T("BORDER"),
		_T("MIRRORONCE"),
		_T("FORCE_DWORD")
	};

	const CString const TexturerMagFilter[8] = 
	{
		_T("NONE"),
		_T("POINT"),
		_T("LINEAR"),
		_T("ANISOTROPIC"),
		_T("PYRAMIDALQUAD"),
		_T("GAUSSIANQUAD"),
		_T("CONVOLUTIONMONO"),
		_T("FORCE_DWORD")
	};

	const CString const TextureMaxMipLevel[4] = 
	{
		_T("0"),
		_T("1"),
		_T("2"),
		_T("3")
	};

	enum UIColor
	{
		White = 0xffffffff,
		Red = 0xffff0000,
		Green = 0xff00ff00,
		Blue = 0xff0000ff,
		Black = 0xff000000,
		Gray = 0xfff0f0f0,
		Seablue = 0xff006994,
		Chocolate = 0xffd2691e,
	};

	// 一些默认的绘制参数
	enum UIDrawParams
	{
		DefaultBorderWidth = 3,
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//
	enum Borders
	{
		LeftBorder,
		RightBorder,
		TopBorder,
		BottomBorder,
		MainRect
	};

	struct SPoint2D
	{
		float X, Y;
		SPoint2D() : X(0), Y(0)
		{

		}

		SPoint2D(float x, float y) : X(x), Y(y)
		{

		}

	};

	struct SMouseState
	{
		SPoint2D CurPos;
		float OffsetX, OffsetY;
		DWORD Message;
		WPARAM wParam;
		SPoint2D SliderPos;
		float ScaleX, ScaleY;
		enum
		{
			MouseOut,
			MouseIn
		};
	};

	extern SMouseState G_MouseState;

	void UpdateMouseState(CRect& rc, float curPosX, float curPosY, DWORD mouseMSg, DWORD nFlags);

	class UIObject;
	class SUIWindow;
	class UIMgr;

	struct UIEventHandle
	{
		virtual void call() = 0;
	};

	// 点击按钮的处理函数的类型为 void(*)(void)

	struct ButtonClickEvent : public UIEventHandle
	{
		ButtonClickEvent(void(SUIWindow::*fun)(UIObject*), SUIWindow* obj)
		{
			WND = obj;
			Function = fun;
		}

		virtual void call()
		{
			(WND->*Function)(Btn);
		}
		UIObject* Btn;
	protected:
		void(SUIWindow::*Function)(UIObject*);
		SUIWindow* WND;
	};

	//////////////////////////////////////////////////////////////////////////
	//
	// UIObject

	class UIObject
	{
	public:
		UIObject(UIObject* parent = NULL);
		virtual ~UIObject();
	public:
		UIObject* Parent;
		CString Name;
		CString ID;
		DWORD TextColor;
		std::vector<UIObject*> Children;
		UIMgr* uiMgr;
		BOOL M_VISITED = FALSE;
	protected:
		std::vector<UIObject*> Subjects;
		std::map<CString, UIEventHandle*> EventMap;

		void AddEvent(CString& eventID, UIEventHandle* handler);

	public:
		void AddSubjects(UIObject* o);

		void DetachSubject(CString& name);

		void DetachSubject(UIObject* o);

		std::vector<UIObject*>& GetSubjects();

		void invokeEvent(CString& eventID);

		BOOL eventExist(CString& eventID);

		UIEventHandle* GetEventAhndle(CString& eventID);
	public:
		virtual DWORD CheckMouse(float mouseX, float mouseY);
		virtual void Move(float offsetX, float offsetY);
		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void NotifyAllSubjects();
		virtual void Update();
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);
		virtual void EditObject();
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//
	class UIRect : public UIObject
	{
	public:
		enum 
		{
			LeftTop,
			LeftBottom,
			RightTop,
			RightBottom,
		};
		struct SUIVertexFMT
		{
			float x, y, z;
			float rhw;
			D3DCOLOR diffuse;

			SUIVertexFMT() :
				x(0), y(0), z(0.5f), rhw(1.0f), diffuse(UIColor::Black)
			{

			}

			SUIVertexFMT(float X, float Y, float Z, float RHW, DWORD c) :
				x(X), y(Y), z(Z), rhw(RHW), diffuse(c)
			{

			}

			static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
		};
		UIRect(float left, float top, float width, float height, 
			UIObject* parent = NULL, DWORD color = UIColor::Seablue);
		virtual ~UIRect();
	public:
		virtual DWORD CheckMouse(float mouseX, float mouseY);
		virtual void Move(float offsetX, float offsetY);
		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void ChangeColor(DWORD color);
	public:
		float Left;
		float Top;
		float Height;
		float Width;
	protected:
		SUIVertexFMT m_vertices[4];
		DWORD m_indices[6];
	};

	struct SUIButtonState
	{
		enum 
		{
			// 当鼠标按下按钮的时候按钮处于该	状态
			BTN_PRESSED,
			// 按钮处于正常状态，
			// 鼠标左键松开并且鼠标处于按钮有效范围内的时候触发按钮被按下的事件，
			// 否则不触发按钮被按下的事件
			BTN_NORMAL,
			// check box 被激活
			BTN_CHECKED,
			// check box 没有被激活
			BTN_UNCHECKED,
		};

		DWORD State;
		time_t Time;	// 该时间戳用来进行按钮动画控制
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//
	class SUIButton : public UIRect
	{
	public:
		enum 
		{
			LINK_NONE,
			LINK_IN,
			LINK_OUT
		};
	protected:
		SUIButtonState BtnState;
		UIRect* Border[5];
		RECT TextRc;
	public:
		std::vector<SUIButton*> IN_BTN;		// 入边
		std::vector<SUIButton*> OUT_BTN;	// 出边 
	public:
		SUIButton(float x, float y, float width, float height, float borderWidth, UIObject* parent);
		virtual ~SUIButton();

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);

		void ChangeBorderColor(DWORD color);

	public:
		DWORD Usage;
	};


	//////////////////////////////////////////////////////////////////////////
	//
	//

	class SUICheck : public UIRect
	{
	protected:
		enum
		{
			CHECK_RECT_SIZE = 10
		};
	protected:
		SUIButtonState BtnState;
		UIRect* Border[5];
		RECT TextRc;
	public:
		SUICheck(float x, float y, float width, float height, float borderWidth, UIObject* parent);
		virtual ~SUICheck();

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);

		void ChangeBorderColor(DWORD color);
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//

	class SUISlider : public UIRect
	{
	protected:
		enum 
		{
			MaxText,
			MinText,
			ValueText,
			CtrlMinHeight = 70,
			CtrlMinWidth = 270,
			CartSize = 14
		};
		SUIButtonState BtnState;
		UIRect* Border[5];
		UIRect* SliderLine;
		UIRect* Cart;
		RECT TextRcs[3];
	public:
		SUISlider(float x, float y, float width, float height, float borderWidth, UIObject* parent);
		virtual ~SUISlider();
	public:
		float MaxValue;
		float MinValue;
		float SliderPos;
		float Range;

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);
	};

	///////////////////////////////////////////////////////////////////////////
	//
	//

	class SUILabel : public UIRect
	{
	protected:
		enum
		{
			ACTIVE,
			NORMAL
		};
	protected:
		UIRect* Border[5];
		RECT TextRc;
		BOOL DrawBorder;
	public:
		SUILabel(float x, float y, float width, float height, float borderWidth, UIObject* parent);
		virtual ~SUILabel();

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);
		virtual void EditObject();

		void ChangeBorderColor(DWORD color);
		void ShowBorder(BOOL b);
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//

	class SUIFloatLabel : public SUILabel
	{
	public:
		SUIFloatLabel::SUIFloatLabel(float x, float y, float width, float height,
			float borderWidth, UIObject* parent);
		virtual ~SUIFloatLabel();
			
		virtual void EditObject();
	public:
		float m_value;
		float m_min;
		float m_max;
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//

	class UIImage : public UIObject
	{
	public:
		enum
		{
			LeftTop,
			LeftBottom,
			RightTop,
			RightBottom,
		};
		struct SUIVertexFMT
		{
			float x, y, z;
			float rhw;
			D3DCOLOR diffuse;
			float u, v;

			SUIVertexFMT() :
				x(0), y(0), z(0.5f), rhw(1.0f), diffuse(UIColor::White)
			{

			}

			SUIVertexFMT(float X, float Y, float Z, float RHW, float U, float V, DWORD c = UIColor::White) :
				x(X), y(Y), z(Z), rhw(RHW), diffuse(c), u(U), v(V)
			{

			}

			static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
		};
		UIImage(float left, float top, float width, float height,
			UIObject* parent = NULL, DWORD color = UIColor::White);
		virtual ~UIImage();
	public:
		virtual DWORD CheckMouse(float mouseX, float mouseY);
		virtual void Move(float offsetX, float offsetY);
		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void SetTexture(CString& path);
	public:
		float Left;
		float Top;
		float Height;
		float Width;
		CString ImagePath;
		LPDIRECT3DDEVICE9 Device = NULL;
	protected:
		SUIVertexFMT m_vertices[4];
		DWORD m_indices[6];
		LPDIRECT3DTEXTURE9 m_texture = NULL;
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//
	class SUIImage : public UIRect
	{
	protected:
		SUIButtonState BtnState;
		UIRect* Border[4];
	public:

		SUIImage(float x, float y, float width, float height, float borderWidth, UIObject* parent);
		virtual ~SUIImage();

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);
		virtual void SetTexture(CString& path);
		virtual void EditObject();

		void ChangeBorderColor(DWORD color);

	public:
		SSamplerState m_samplerState;
		UIImage* Image;
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//

	class SUIWindow : public SUILabel
	{
	protected:
		enum 
		{
			WND_ACTIVE,
			WND_NORMAL,
			WND_DRAG,
		};
	public:
		SUIWindow(float x, float y, float width, float height, 
			float borderWidth = UIDrawParams::DefaultBorderWidth, UIObject* parent = NULL);
		virtual ~SUIWindow();

		virtual void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);
		virtual void Move(float offsetX, float offsetY);
		virtual void OnMouse(SMouseState& mouse);
		virtual void ChangeColor(DWORD color);
		virtual void SetImage(CString& path);
		virtual CString GenCode(DWORD sh = PSH_CODE);
		virtual CString SyntaxTreeGenCode(DWORD sh = PSH_CODE);

		void ChangeBorderColor(DWORD color);

		void AddLinkButton(UIObject* btn);

	public:
		std::vector<UIObject*> M_OUTPUTS;
		std::vector<UIObject*> M_INPUTS;
		DWORD WND_STATE = WND_NORMAL;
		BOOL isStruct = FALSE;
	};
}