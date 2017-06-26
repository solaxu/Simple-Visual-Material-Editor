#include "stdafx.h"

#include "UI.h"
#include "LabelEditDlg.h"
#include "FloatLabelDlg.h"
#include "SamplerTexDlg.h"

namespace ShaderEditor
{
	//////////////////////////////////////////////////////////////////////////
	//
	//

	SMouseState G_MouseState = {
		{ 0.0f, 0.0f },
		0.0f,0.0f,
		WM_MOUSEMOVE,
		0,
		{ 0.0f, 0.0f }
	};

	void UpdateMouseState(CRect& rc, float curPosX, float curPosY, DWORD mouseMSg, DWORD nFlags)
	{
		G_MouseState.ScaleX = rc.Width() / 2048.0f;
		G_MouseState.ScaleY = rc.Height() / 1024.0f;
		G_MouseState.wParam = nFlags;

		float TX = curPosX / G_MouseState.ScaleX;
		float TY = curPosY / G_MouseState.ScaleY;

		G_MouseState.OffsetX = TX - G_MouseState.CurPos.X;
		G_MouseState.OffsetY = TY - G_MouseState.CurPos.Y;

		G_MouseState.CurPos.X = TX;
		G_MouseState.CurPos.Y = TY;
		G_MouseState.Message = mouseMSg;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	UIObject::UIObject(UIObject* parent) :Parent(parent),TextColor(UIColor::Black),uiMgr(NULL)
	{
		if (parent)
		{
			parent->Children.push_back(this);
		}
	}

	UIObject::~UIObject()
	{
		for (auto it = EventMap.begin(); it != EventMap.end(); ++it)
		{
			delete it->second;
		}
	}

	void UIObject::AddSubjects(UIObject* o)
	{
		Subjects.push_back(o);
	}

	void UIObject::DetachSubject(CString& name)
	{
		for (auto it = Subjects.begin(); it != Subjects.end(); ++it)
		{
			auto ptr = *it;
			if (ptr->Name == name)
			{
				Subjects.erase(it);
				return;
			}
		}
	}

	void UIObject::DetachSubject(UIObject* o)
	{
		for (auto it = Subjects.begin(); it != Subjects.end(); ++it)
		{
			auto ptr = *it;
			if (ptr == o)
			{
				Subjects.erase(it);
				return;
			}
		}
	}

	void UIObject::Move(float offsetX, float offsetY)
	{

	}

	void UIObject::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{

	}

	void UIObject::NotifyAllSubjects()
	{

	}

	void UIObject::Update()
	{

	}

	void UIObject::OnMouse(SMouseState& mouse)
	{
		for each(auto ptr in Children)
		{
			ptr->OnMouse(mouse);
		}
	}

	void UIObject::AddEvent(CString& eventID, UIEventHandle* handler)
	{
		EventMap[eventID] = handler;
	}

	void UIObject::invokeEvent(CString& eventID)
	{
		EventMap[eventID]->call();
	}

	void UIObject::EditObject()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//

	UIEventHandle* UIObject::GetEventAhndle(CString& eventID)
	{
		auto it = EventMap.find(eventID);
		if (it == EventMap.end())
		{
			return NULL;
		}
		return EventMap[eventID];
	}

	BOOL UIObject::eventExist(CString& eventID)
	{
		if (EventMap.find(eventID) != EventMap.end())
		{
			return TRUE;
		}
		return FALSE;
	}

	std::vector<UIObject*>& UIObject::GetSubjects()
	{
		return Subjects;
	}

	void UIObject::ChangeColor(DWORD color)
	{

	}

	DWORD UIObject::CheckMouse(float mouseX, float mouseY)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//

	UIRect::UIRect(float left, float top, float width, float height, UIObject* parent, DWORD color):
		Left(left), Top(top), Width(width), Height(height),
		UIObject(parent)
	{
		m_vertices[LeftTop].x = left;
		m_vertices[LeftTop].y = top;
		m_vertices[LeftTop].diffuse = color;

		m_vertices[LeftBottom].x = left;
		m_vertices[LeftBottom].y = top + height;
		m_vertices[LeftBottom].diffuse = color;

		m_vertices[RightTop].x = left + width;
		m_vertices[RightTop].y = top;
		m_vertices[RightTop].diffuse = color;

		m_vertices[RightBottom].x = left + width;
		m_vertices[RightBottom].y = top + height;
		m_vertices[RightBottom].diffuse = color;

		m_indices[0] = LeftBottom;
		m_indices[1] = LeftTop;
		m_indices[2] = RightTop;
		m_indices[3] = LeftBottom;
		m_indices[4] = RightTop;
		m_indices[5] = RightBottom;
	}

	UIRect::~UIRect()
	{

	}

	void UIRect::ChangeColor(DWORD color)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vertices[i].diffuse = color;
		}
	}

	void UIRect::Move(float offsetX, float offsetY)
	{
		Left += offsetX;
		Top += offsetY;

		m_vertices[LeftTop].x = Left;
		m_vertices[LeftTop].y = Top;

		m_vertices[LeftBottom].x = Left;
		m_vertices[LeftBottom].y = Top + Height;

		m_vertices[RightTop].x = Left + Width;
		m_vertices[RightTop].y = Top;

		m_vertices[RightBottom].x = Left + Width;
		m_vertices[RightBottom].y = Top + Height;
	}

	void UIRect::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		if (device)
		{
			HRESULT hr = device->SetFVF(SUIVertexFMT::FVF);
			if (FAILED(device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, (void*)m_indices,
				D3DFMT_INDEX32, (void*)m_vertices, sizeof(SUIVertexFMT) )))
			{
				// test
				MessageBox(NULL, _T("asdd"), _T("sd"), MB_OK);
				return;
			}
		}
	}

	DWORD UIRect::CheckMouse(float mouseX, float mouseY)
	{
		float Right = Left + Width;
		float Bottom = Top + Height;
		if (mouseX > Left && mouseX < Right && mouseY > Top && mouseY < Bottom)
			return SMouseState::MouseIn;
		return SMouseState::MouseOut;
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	SUIButton::SUIButton(float x, float y, float width, float height, 
		float borderWidth, UIObject* parent):Usage(LINK_NONE),
		UIRect(x, y, width, height, parent)
	{
		Border[Borders::LeftBorder] = new UIRect(x, y, borderWidth, height);
		Border[Borders::RightBorder] = new UIRect(x + width - borderWidth, y, borderWidth, height);
		Border[Borders::TopBorder] = new UIRect(x + borderWidth, y, width - borderWidth * 2, borderWidth);
		Border[Borders::BottomBorder] = new UIRect(x + borderWidth, y + height - borderWidth, width - borderWidth * 2, borderWidth);
		Border[Borders::MainRect] = new UIRect(x + borderWidth, y + borderWidth, width - borderWidth * 2, height - borderWidth * 2);

		BtnState.State = SUIButtonState::BTN_NORMAL;
		Border[Borders::MainRect]->ChangeColor(UIColor::Gray);
	}

	SUIButton::~SUIButton()
	{
		for (int i = 0; i < 5; ++i)
		{
			delete Border[i];
		}
	}

	void SUIButton::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Draw(device, font);
		}
		TextRc.left = Border[MainRect]->Left;
		TextRc.right = Border[MainRect]->Left + Border[MainRect]->Width;
		TextRc.top = Border[MainRect]->Top;
		TextRc.bottom = Border[MainRect]->Top + Border[MainRect]->Height;

		font->DrawText(NULL, Name, Name.GetLength(), &TextRc,
			DT_CENTER | DT_SINGLELINE | DT_NOCLIP | DT_VCENTER, TextColor);
	}

	void SUIButton::Move(float offsetX, float offsetY)
	{
		Left += offsetX;
		Top += offsetY;
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Move(offsetX, offsetY);
		}
	}

	void SUIButton::ChangeBorderColor(DWORD color)
	{
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->ChangeColor(color);
		}
	}

	void SUIButton::ChangeColor(DWORD color)
	{
		Border[MainRect]->ChangeColor(color);
	}

	void SUIButton::OnMouse(SMouseState& mouse)
	{
// 		if (mouse.Message == WM_MOUSEMOVE && mouse.wParam & MK_LBUTTON)
// 		{
// 			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
// 			{
// 				BtnState.State = SUIButtonState::BTN_PRESSED;
// 				// 将消息传递给Button的Parent， 如果它的parent没有对应的处理项，那么
// 				// 传递给Parent的Parent直到最顶层的UIObject位置
// 				UIObject* temp = Parent;
// 				while (temp)
// 				{
// 					CString evtID(_T("AddToLink"));
// 					if (temp->eventExist(evtID))
// 					{
// 						ButtonClickEvent* it = dynamic_cast<ButtonClickEvent*>(temp->GetEventAhndle(evtID));
// 						if (it == NULL)
// 							return;
// 						it->Btn = this;
// 						temp->invokeEvent(evtID);
// 						break;
// 					}
// 					temp = temp->Parent;
// 				}
// 			}
// 		}

		if (BtnState.State == SUIButtonState::BTN_NORMAL &&
			(mouse.Message == WM_LBUTTONDOWN || mouse.Message == WM_LBUTTONUP))
		{
			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				BtnState.State = SUIButtonState::BTN_PRESSED;
				// 将消息传递给Button的Parent， 如果它的parent没有对应的处理项，那么
				// 传递给Parent的Parent直到最顶层的UIObject位置
				UIObject* temp = Parent;
				while (temp)
				{
					CString evtID(_T("AddToLink"));
					if (temp->eventExist(evtID))
					{
						ButtonClickEvent* it = dynamic_cast<ButtonClickEvent*>(temp->GetEventAhndle(evtID));
						if (it == NULL)
							return;
						it->Btn = this;
						temp->invokeEvent(evtID);
						break;
					}
					temp = temp->Parent;
				}
			}
			return;
		}

		if (BtnState.State == SUIButtonState::BTN_PRESSED &&
			mouse.Message == WM_LBUTTONUP)
		{
			BtnState.State = SUIButtonState::BTN_NORMAL;
			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				// 将消息传递给Button的Parent， 如果它的parent没有对应的处理项，那么
				// 传递给Parent的Parent直到最顶层的UIObject位置
				UIObject* temp = Parent;
				while (temp)
				{
					if (temp->eventExist(ID))
					{
						temp->invokeEvent(ID);
						break;
					}
					temp = temp->Parent;
				}
				return;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//

	SUICheck::SUICheck(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) :
		UIRect(x, y, width, height, parent)
	{
		height = borderWidth * 2 + CHECK_RECT_SIZE;
		width = borderWidth * 2 + CHECK_RECT_SIZE;
		float up = y + (Height - height) / 2;
		Border[Borders::LeftBorder] = new UIRect(x, up, borderWidth, height);
		Border[Borders::RightBorder] = new UIRect(x + width - borderWidth, up, borderWidth, height);
		Border[Borders::TopBorder] = new UIRect(x + borderWidth, up, width - borderWidth * 2, borderWidth);
		Border[Borders::BottomBorder] = new UIRect(x + borderWidth, up + height - borderWidth, width - borderWidth * 2, borderWidth);
		Border[Borders::MainRect] = new UIRect(x + borderWidth, up + borderWidth, width - borderWidth * 2, height - borderWidth * 2);

		BtnState.State = SUIButtonState::BTN_UNCHECKED;
	}

	SUICheck::~SUICheck()
	{
		for (int i = 0; i < 5; ++i)
		{
			delete Border[i];
		}
	}

	void SUICheck::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		if (BtnState.State == SUIButtonState::BTN_CHECKED)
			Border[MainRect]->ChangeColor(UIColor::Green);
		else
			Border[MainRect]->ChangeColor(UIColor::Gray);

		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Draw(device, font);
		}

		TextRc.left = Border[RightBorder]->Left + Border[MainRect]->Width;
		TextRc.right = Left + Width;
		TextRc.top = Top;
		TextRc.bottom = Top + Height;

		font->DrawText(NULL, Name, Name.GetLength(), &TextRc,
			DT_LEFT | DT_SINGLELINE | DT_NOCLIP | DT_VCENTER, TextColor);
	}

	void SUICheck::Move(float offsetX, float offsetY)
	{
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Move(offsetX, offsetY);
		}
	}

	void SUICheck::ChangeBorderColor(DWORD color)
	{
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->ChangeColor(color);
		}
	}

	void SUICheck::ChangeColor(DWORD color)
	{
		Border[MainRect]->ChangeColor(color);
	}

	void SUICheck::OnMouse(SMouseState& mouse)
	{
		if (BtnState.State == SUIButtonState::BTN_UNCHECKED &&
			mouse.Message == WM_LBUTTONDOWN)
		{
			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
				BtnState.State = SUIButtonState::BTN_CHECKED;
		}

		if (BtnState.State == SUIButtonState::BTN_CHECKED &&
			mouse.Message == WM_LBUTTONUP)
		{
			BtnState.State = SUIButtonState::BTN_UNCHECKED;
			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				UIObject* temp = Parent;
				while (temp)
				{
					if (temp->eventExist(ID))
					{
						temp->invokeEvent(ID);
						break;
					}
					temp = temp->Parent;
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//

	SUISlider::SUISlider(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) : Range(100.0f),MaxValue(100.0f),MinValue(0.0f),SliderPos(0.0f),
		UIRect(x, y, width, height, parent)
	{
		height = height > CtrlMinHeight ? height : CtrlMinHeight;
		width = width > CtrlMinWidth ? width : CtrlMinWidth;
		
		Width = width;
		Height = height;

		Border[Borders::LeftBorder] = new UIRect(x, y, borderWidth, height);
		Border[Borders::RightBorder] = new UIRect(x + width - borderWidth, y, borderWidth, height);
		Border[Borders::TopBorder] = new UIRect(x + borderWidth, y, width - borderWidth * 2, borderWidth);
		Border[Borders::BottomBorder] = new UIRect(x + borderWidth, y + height - borderWidth, width - borderWidth * 2, borderWidth);
		Border[Borders::MainRect] = new UIRect(x + borderWidth, y + borderWidth, width - borderWidth * 2, height - borderWidth * 2);

		SliderLine = new UIRect(x + borderWidth + 2, y + Height / 2 - 2, width - (borderWidth + 2) * 2, borderWidth);

		Cart = new UIRect(x + borderWidth + 2, y + Height / 2 - 7, CartSize, CartSize);

		BtnState.State = SUIButtonState::BTN_NORMAL;
	}

	SUISlider::~SUISlider()
	{
		for (int i = 0; i < 5; ++i)
		{
			delete Border[i];
		}
	}

	void SUISlider::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Draw(device, font);
		}

		TextRcs[MinText].left = Border[LeftBorder]->Left + Border[LeftBorder]->Width;
		TextRcs[MinText].right = TextRcs[MinText].left + Border[MainRect]->Width / 2;
		TextRcs[MinText].top = Border[MainRect]->Top + 2.0f;
		TextRcs[MinText].bottom = Border[MainRect]->Top + 20.0f;

		CString str;
		str.Format(_T("Min [ %3.2f ]"), MinValue);
		font->DrawText(NULL, str, str.GetLength(), &TextRcs[MinText],
			DT_LEFT | DT_SINGLELINE | DT_NOCLIP | DT_VCENTER, TextColor);

		TextRcs[MaxText].left = TextRcs[MinText].right;
		TextRcs[MaxText].right = TextRcs[MaxText].left + Border[MainRect]->Width / 2;
		TextRcs[MaxText].top = TextRcs[MinText].top;
		TextRcs[MaxText].bottom = TextRcs[MinText].bottom;

		str = _T("");
		str.Format(_T("[ %3.2f ] Max"), MaxValue);
		font->DrawText(NULL, str, str.GetLength(), &TextRcs[MaxText],
			DT_RIGHT | DT_SINGLELINE | DT_NOCLIP | DT_VCENTER, TextColor);

		TextRcs[ValueText].left = TextRcs[MinText].left;
		TextRcs[ValueText].right = TextRcs[MaxText].right;
		TextRcs[ValueText].top = Border[BottomBorder]->Top - 25.0f;
		TextRcs[ValueText].bottom = Border[BottomBorder]->Top - 5.0f;

		str = _T("");
		str.Format(_T("[ %3.2f ]"), SliderPos);
		font->DrawText(NULL, str, str.GetLength(), &TextRcs[ValueText],
			DT_CENTER | DT_SINGLELINE | DT_NOCLIP | DT_VCENTER, TextColor);

		SliderLine->Draw(device, font);
		Cart->Draw(device, font);
	}

	void SUISlider::Move(float offsetX, float offsetY)
	{
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Move(offsetX, offsetY);
		}
		SliderLine->Move(offsetX, offsetY);
		Cart->Move(offsetX, offsetY);
	}

	void SUISlider::ChangeColor(DWORD color)
	{
		Border[MainRect]->ChangeColor(color);
	}

	void SUISlider::OnMouse(SMouseState& mouse)
	{
		if (mouse.Message == WM_MOUSEMOVE && mouse.wParam & MK_LBUTTON)
		{
			if (Cart->CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				SliderPos += mouse.OffsetX;
				float scale = SliderPos / Range * SliderLine->Width;
				Cart->Left += scale;

				UIObject* temp = Parent;
				while (temp)
				{
					if (temp->eventExist(ID))
					{
						temp->invokeEvent(ID);
						break;
					}
					temp = temp->Parent;
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	
	SUILabel::SUILabel(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) : 
		UIRect(x, y, width, height, parent), DrawBorder(FALSE)
	{
		Border[Borders::LeftBorder] = new UIRect(x, y, borderWidth, height);
		Border[Borders::RightBorder] = new UIRect(x + width - borderWidth, y, borderWidth, height);
		Border[Borders::TopBorder] = new UIRect(x + borderWidth, y, width - borderWidth * 2, borderWidth);
		Border[Borders::BottomBorder] = new UIRect(x + borderWidth, y + height - borderWidth, width - borderWidth * 2, borderWidth);
		Border[Borders::MainRect] = new UIRect(x + borderWidth, y + borderWidth, width - borderWidth * 2, height - borderWidth * 2);
		
		Border[Borders::MainRect]->ChangeColor(UIColor::Gray);
	}

	SUILabel::~SUILabel()
	{
		for (int i = 0; i < 5; ++i)
		{
			delete Border[i];
		}
	}

	void SUILabel::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		if (DrawBorder)
		{
			for (int i = 0; i < 5; ++i)
			{
				Border[i]->Draw(device, font);
			}
		}
		TextRc.left = Border[MainRect]->Left;
		TextRc.right = Border[MainRect]->Left + Border[MainRect]->Width;
		TextRc.top = Border[MainRect]->Top;
		TextRc.bottom = Border[MainRect]->Top + Border[MainRect]->Height;

		font->DrawText(NULL, Name, Name.GetLength(), &TextRc,
			DT_CENTER | DT_NOCLIP | DT_VCENTER, TextColor);
	}

	void SUILabel::Move(float offsetX, float offsetY)
	{
		Left += offsetX;
		Top += offsetY;
		for (int i = 0; i < 5; ++i)
		{
			Border[i]->Move(offsetX, offsetY);
		}
	}

	void SUILabel::ChangeBorderColor(DWORD color)
	{
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->ChangeColor(color);
		}
	}

	void SUILabel::ShowBorder(BOOL b)
	{
		DrawBorder = b;
	}

	void SUILabel::ChangeColor(DWORD color)
	{
		Border[MainRect]->ChangeColor(color);
	}

	void SUILabel::OnMouse(SMouseState& mouse)
	{
		
	}

	void SUILabel::EditObject()
	{
		CLabelEditDlg dlg;
		dlg.text = Name;
		if (IDOK == dlg.DoModal())
		{
			Name = dlg.text;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	SUIFloatLabel::SUIFloatLabel(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) : m_value(0.0f),m_max(100.0f),m_min(0.0f),
		SUILabel(x, y, width, height, borderWidth, parent)
	{

	}

	SUIFloatLabel::~SUIFloatLabel()
	{

	}

	void SUIFloatLabel::EditObject()
	{
		CFloatLabelDlg dlg;
		dlg.value = m_value;
		dlg.M_MIN = m_min;
		dlg.M_MAX = m_max;
		if (IDOK == dlg.DoModal())
		{
			Name = _T("");
			m_value = dlg.value;
			m_min = dlg.M_MIN;
			m_max = dlg.M_MAX;
			Name.Format(_T("[ %3.2f ]"), m_value);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//

	UIImage::UIImage(float left, float top, float width, float height, UIObject* parent, DWORD color) :
		Left(left), Top(top), Width(width), Height(height), m_texture(NULL),
		UIObject(parent)
	{
		m_vertices[LeftTop].x = left;
		m_vertices[LeftTop].y = top;
		m_vertices[LeftTop].diffuse = color;
		m_vertices[LeftTop].u = 0.0f;
		m_vertices[LeftTop].v = 0.0f;

		m_vertices[LeftBottom].x = left;
		m_vertices[LeftBottom].y = top + height;
		m_vertices[LeftBottom].diffuse = color;
		m_vertices[LeftBottom].u = 0.0f;
		m_vertices[LeftBottom].v = 1.0f;

		m_vertices[RightTop].x = left + width;
		m_vertices[RightTop].y = top;
		m_vertices[RightTop].diffuse = color;
		m_vertices[RightTop].u = 1.0f;
		m_vertices[RightTop].v = 0.0f;

		m_vertices[RightBottom].x = left + width;
		m_vertices[RightBottom].y = top + height;
		m_vertices[RightBottom].diffuse = color;
		m_vertices[RightBottom].u = 1.0f;
		m_vertices[RightBottom].v = 1.0f;

		m_indices[0] = LeftBottom;
		m_indices[1] = LeftTop;
		m_indices[2] = RightTop;
		m_indices[3] = LeftBottom;
		m_indices[4] = RightTop;
		m_indices[5] = RightBottom;
	}

	UIImage::~UIImage()
	{
		if (m_texture)
		{
			m_texture->Release();
			m_texture = NULL;
		}
	}

	void UIImage::Move(float offsetX, float offsetY)
	{
		Left += offsetX;
		Top += offsetY;

		m_vertices[LeftTop].x = Left;
		m_vertices[LeftTop].y = Top;

		m_vertices[LeftBottom].x = Left;
		m_vertices[LeftBottom].y = Top + Height;

		m_vertices[RightTop].x = Left + Width;
		m_vertices[RightTop].y = Top;

		m_vertices[RightBottom].x = Left + Width;
		m_vertices[RightBottom].y = Top + Height;
	}

	void UIImage::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		if (device)
		{
			HRESULT hr = device->SetFVF(SUIVertexFMT::FVF);
			hr = device->SetTexture(0, m_texture);
			if (FAILED(device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, (void*)m_indices,
				D3DFMT_INDEX32, (void*)m_vertices, sizeof(SUIVertexFMT))))
			{
				// test
				MessageBox(NULL, _T("asdd"), _T("sd"), MB_OK);
				return;
			}
			hr = device->SetTexture(0, 0);
		}
	}

	DWORD UIImage::CheckMouse(float mouseX, float mouseY)
	{
		float Right = Left + Width;
		float Bottom = Top + Height;
		if (mouseX > Left && mouseX < Right && mouseY > Top && mouseY < Bottom)
			return SMouseState::MouseIn;
		return SMouseState::MouseOut;
	}

	void UIImage::SetTexture(CString& path)
	{
		ImagePath = path;
		if (m_texture)
		{
			m_texture->Release();
			m_texture = NULL;
		}
		D3DXCreateTextureFromFile(Device, ImagePath, &m_texture);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	SUIImage::SUIImage(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) :
		UIRect(x, y, width, height, parent)
	{
		Border[Borders::LeftBorder] = new UIRect(x, y, borderWidth, height);
		Border[Borders::RightBorder] = new UIRect(x + width - borderWidth, y, borderWidth, height);
		Border[Borders::TopBorder] = new UIRect(x + borderWidth, y, width - borderWidth * 2, borderWidth);
		Border[Borders::BottomBorder] = new UIRect(x + borderWidth, y + height - borderWidth, width - borderWidth * 2, borderWidth);
		Image = new UIImage(x + borderWidth, y + borderWidth, width - borderWidth * 2, height - borderWidth * 2);
	}

	SUIImage::~SUIImage()
	{
		for (int i = 0; i < 4; ++i)
		{
			delete Border[i];
		}
		delete Image;
	}

	void SUIImage::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->Draw(device, font);
		}
		Image->Draw(device, font);
	}

	void SUIImage::Move(float offsetX, float offsetY)
	{
		Left += offsetX;
		Top += offsetY;
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->Move(offsetX, offsetY);
		}
		Image->Move(offsetX, offsetY);
	}

	void SUIImage::ChangeBorderColor(DWORD color)
	{
		for (int i = 0; i < 4; ++i)
		{
			Border[i]->ChangeColor(color);
		}
	}

	void SUIImage::ChangeColor(DWORD color)
	{
		Image->ChangeColor(color);
	}

	void SUIImage::OnMouse(SMouseState& mouse)
	{
		
	}

	void SUIImage::SetTexture(CString& path)
	{
		Image->SetTexture(path);
	}

	void SUIImage::EditObject()
	{
		CSamplerTexDlg dlg;

		for (int i = 0; i < 6; ++i)
		{
			if (m_samplerState.addressU == TextureAddress[i])
				dlg.AddrU = i;
			if (m_samplerState.addressV == TextureAddress[i])
				dlg.AddrV = i;
			if (m_samplerState.addressW == TextureAddress[i])
				dlg.AddrW = i;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (m_samplerState.maxMipLevel == TextureMaxMipLevel[i])
				dlg.MaxMipLvl = i;
		}

		for (int i = 0; i < 8; ++i)
		{
			if (m_samplerState.magFilter == TexturerMagFilter[i])
				dlg.FilterMag = i;
			if (m_samplerState.minFilter == TexturerMagFilter[i])
				dlg.FilterMin = i;
			if (m_samplerState.mipFilter == TexturerMagFilter[i])
				dlg.FilterMip = i;
		}

		DWORD borderColor = _ttol(m_samplerState.borderColor);

		dlg.BorderA = (borderColor & 0xff000000) >> 24;
		dlg.BorderR = (borderColor & 0x00ff0000) >> 16;
		dlg.BorderG = (borderColor & 0x0000ff00) >> 8;
		dlg.BorderB= borderColor & 0x000000ff;

		dlg.TexPath = Image->ImagePath;

		if (IDOK == dlg.DoModal())
		{
			m_samplerState.addressU = TextureAddress[dlg.AddrU];
			m_samplerState.addressV = TextureAddress[dlg.AddrV];
			m_samplerState.addressW = TextureAddress[dlg.AddrW];

			m_samplerState.borderColor = _T("");
			m_samplerState.borderColor.Format(_T("%d"), MakeColor(dlg.BorderA, dlg.BorderR, dlg.BorderG, dlg.BorderB));

			m_samplerState.magFilter = TexturerMagFilter[dlg.FilterMag];
			m_samplerState.minFilter = TexturerMagFilter[dlg.FilterMin];
			m_samplerState.mipFilter = TexturerMagFilter[dlg.FilterMip];

			m_samplerState.maxMipLevel = TextureMaxMipLevel[dlg.MaxMipLvl];

			Image->SetTexture(dlg.TexPath);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//

	SUIWindow::SUIWindow(float x, float y, float width, float height,
		float borderWidth, UIObject* parent) : WND_STATE(WND_NORMAL),
		SUILabel(x, y, width, height, borderWidth, parent)
	{
		ShowBorder(TRUE);

		ButtonClickEvent* evt = new ButtonClickEvent(&SUIWindow::AddLinkButton, this);
		AddEvent(CString(_T("AddToLink")), evt);
	}

	SUIWindow::~SUIWindow()
	{
		
	}

	void SUIWindow::AddLinkButton(UIObject* btn)
	{
		SUIButton* button = dynamic_cast<SUIButton*>(btn);
		if (button == NULL)
			return;
		if (button->Usage == SUIButton::LINK_IN)
		{
			if (M_INPUTS.end() == std::find(M_INPUTS.begin(), M_INPUTS.end(), btn))
				this->M_INPUTS.push_back(btn);
		}
		else if(button->Usage == SUIButton::LINK_OUT)
		{
			if (M_OUTPUTS.end() == std::find(M_OUTPUTS.begin(), M_OUTPUTS.end(), btn))
				this->M_OUTPUTS.push_back(btn);
		}
	}

	void SUIWindow::Draw(LPDIRECT3DDEVICE9 device, LPD3DXFONT font)
	{
		ChangeBorderColor(UIColor::Chocolate);
		
		SUILabel::Draw(device, font);
	}

	void SUIWindow::Move(float offsetX, float offsetY)
	{
		SUILabel::Move(offsetX, offsetY);

		for each (auto ptr in Children)
		{
			ptr->Move(offsetX, offsetY);
		}
	}

	void SUIWindow::ChangeBorderColor(DWORD color)
	{
		SUILabel::ChangeBorderColor(color);
	}

	void SUIWindow::ChangeColor(DWORD color)
	{
		SUILabel::ChangeColor(color);
	}

	void SUIWindow::SetImage(CString& path)
	{
		
	}

	void SUIWindow::OnMouse(SMouseState& mouse)
	{ 
		static float dragStartX = 0;
		static float dragStartY = 0;

		for each (auto ptr in Children)
		{
			ptr->OnMouse(mouse);
		}

		if (mouse.Message == WM_MOUSEMOVE && WND_STATE == WND_ACTIVE)
		{
			if ((mouse.wParam & MK_LBUTTON) && CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				dragStartX = mouse.CurPos.X;
				dragStartY = mouse.CurPos.Y;
				WND_STATE = WND_DRAG;
				return;
			}
		}

		if (mouse.Message == WM_LBUTTONUP && WND_STATE == WND_DRAG)
		{
			float offsetX = mouse.CurPos.X - dragStartX;
			float offsetY = mouse.CurPos.Y - dragStartY;
			Move(offsetX, offsetY);
			WND_STATE = WND_ACTIVE;
			return;
		}

		if (mouse.Message == WM_LBUTTONDOWN && WND_STATE == WND_NORMAL)
		{
			if (CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				WND_STATE = WND_ACTIVE;
				return;
			}
		}

		if (mouse.Message == WM_LBUTTONUP && WND_STATE == WND_ACTIVE)
		{
			if (!CheckMouse(mouse.CurPos.X, mouse.CurPos.Y))
			{
				WND_STATE = WND_NORMAL;
				return;
			}
		}
	}

	CString SUIWindow::GenCode(DWORD sh)
	{
		return _T("");
	}

	CString SUIWindow::SyntaxTreeGenCode(DWORD sh)
	{
		return _T("");
	}
}