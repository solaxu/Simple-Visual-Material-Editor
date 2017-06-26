#pragma once

#include "UI.h"
#include <vector>

namespace ShaderEditor
{
	class UIObject;
	class SUIWindow;
	class SUIButton;
	enum UIDrawParams;
	enum UIColor;


	struct LinksPoint
	{
		float x, y, z, w;
		DWORD diffuse;
		LinksPoint():x(0),y(0),z(0.5f),w(1.0f),diffuse(0xff000000){}
		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	};

	class UIMgr
	{
	public:
		UIMgr();

		virtual ~UIMgr();

		static DWORD m_idSeed;
		std::vector<UIObject*> m_wnds;

	public:

		template<typename UIType>
		UIObject* CreateUI(float x, float y, float width, float height, UIMgr* mgr,
			CString& name, CString& id, 
			UIObject* parent = NULL,
			float borderWidth = UIDrawParams::DefaultBorderWidth)
		{
			UIType* typePtr =  new UIType(x, y, width, height, borderWidth, parent);
			typePtr->Name = name;
			typePtr->ID = id;
			UIObject* ptr = dynamic_cast<UIObject*>(typePtr);
			if (ptr != NULL)
			{
				ptr->ChangeColor(UIColor::Gray);
				ptr->uiMgr = mgr;
				m_wnds.push_back(ptr);
			}
				
			return ptr;
		};

		template<typename UIType>
		SUIWindow* CreateWnd(float x, float y, float width, float height, UIMgr* mgr,
			CString& name, CString& id, 
			UIObject* parent = NULL)
		{
			UIType* typePtr = new UIType(x, y, width, height, parent);
			
			if (typePtr != NULL)
			{
				typePtr->Name = name;
				typePtr->ID = id;
				typePtr->uiMgr = mgr;
				typePtr->ChangeColor(UIColor::Gray);
				m_wnds.push_back(typePtr);
			}

			return typePtr;
		};

		void Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font);


		void DeleteUI(UIObject* obj);

		void DeleteUI(CString& id);

		UIObject* GetUI(CString& id);

		void Update();

		void CollectLinkLines(LPDIRECT3DDEVICE9 device);

		SUIButton* GetLinkButton();

		UIObject* GetControl();

		SUIWindow* GetWindow();

		CString GenCode(DWORD sh, TiXmlElement* texNode, TiXmlElement* matrixNode);

		static CString GenerateUIID()
		{
			CString str;
			str.Format(_T("%u"), m_idSeed++);
			return str;
		}
	};
}