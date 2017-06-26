// D3D9DockWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ShaderEditor.h"
#include "D3D9DockWnd.h"

#include <vector>
#include <string>

// D3D9DockWnd

IMPLEMENT_DYNAMIC(CD3D9DockWnd, CDockablePane)

CD3D9DockWnd::CD3D9DockWnd()
{
	m_timerIndex = 1;
}

CD3D9DockWnd::~CD3D9DockWnd()
{
}


BEGIN_MESSAGE_MAP(CD3D9DockWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CD3D9DockWnd::InitDirect9()
{
	if (NULL == (m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetSafeHwnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_d3d9Device)))
	{
		return FALSE;
	}

	D3DXLoadMeshFromX(L"sphereearth.x", D3DXMESH_MANAGED, m_d3d9Device, NULL,
		NULL, NULL, NULL, &m_sphere);

	D3DXMatrixIdentity(&m_WorldMat);

	D3DXMatrixRotationY(&m_WorldMat, 45.0f);

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -10);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMat, &vEyePt, &vLookatPt, &vUpVec);

	CRect rc;
	GetClientRect(rc);
	float fAspectRatio = (float)rc.Width() / (float)rc.Height();
	D3DXMatrixPerspectiveFovLH(&m_ProjMat, D3DX_PI / 4, fAspectRatio, 1.0f, 100.0f);

	return TRUE;
}

struct CUSTOMVERTEX
{
	float       x, y, z, w; //顶点位置
	float		u,v;    //顶点颜色
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)

void CD3D9DockWnd::Draw()
{
	CUSTOMVERTEX Vertices[] =
	{
		{ -3,   -3,  0.0f, 1.0f,  0.0f, 1.0f },
		{ -3,    3,  0.0f, 1.0f, 0.0f, 0.0f },
		{ 3,   -3,  0.0f, 1.0f,  1.0f, 1.0f },
		{ 3,    3,  0.0f, 1.0f, 1.0f, 0.0f }
	};

	m_d3d9Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	HRESULT hr = S_OK;

	if (m_effect)
	{
		UINT iPass, cPasses;

		hr = m_effect->Begin(&cPasses, 0);

		for (iPass = 0; iPass < cPasses; ++iPass)
		{
			hr = m_effect->BeginPass(iPass);

			hr = m_d3d9Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertices, sizeof(CUSTOMVERTEX) );

			hr = m_effect->EndPass();
		}
		hr = m_effect->End();
	}
	else
	{
		m_d3d9Device->SetTransform(D3DTS_WORLD, &m_WorldMat);
		m_d3d9Device->SetTransform(D3DTS_VIEW, &m_ViewMat);
		m_d3d9Device->SetTransform(D3DTS_PROJECTION, &m_ProjMat);
		
		hr = m_d3d9Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertices, sizeof(CUSTOMVERTEX));
	}
}

// CD3D9DockWnd 消息处理程序

// 销毁

void CD3D9DockWnd::OnDestroy()
{
	ShaderEditor::SafeReleaseCOM<LPDIRECT3DDEVICE9>(m_d3d9Device);
	ShaderEditor::SafeReleaseCOM<LPDIRECT3D9>(m_d3d9);
	KillTimer(m_timerIndex);

	CDockablePane::OnDestroy();
}

void CD3D9DockWnd::OnTimer(UINT_PTR nIDEvent)
{
	CDockablePane::OnTimer(nIDEvent);

	m_WorldViewMat = m_WorldMat * m_ViewMat;

	m_WorldViewProjMat = m_WorldViewMat * m_ProjMat;

	D3DXMatrixInverse(&m_InvWorldMat, NULL, &m_WorldMat);

	D3DXMatrixInverse(&m_InvViewMat, NULL, &m_ViewMat);

	D3DXMatrixInverse(&m_InvWorldViewMat, NULL, &m_WorldViewMat);

	D3DXMatrixInverse(&m_InvWorldViewProjdMat, NULL, &m_WorldViewProjMat);

	// set render params

	if (m_effect)
	{
		HRESULT hr = S_OK;

		if (FAILED(hr = m_effect->SetTechnique("DefaultTech")))
			return;
		if (FAILED(hr = m_effect->OnResetDevice()))
			return;

		D3DXEFFECT_DESC desc;
		hr = m_effect->GetDesc(&desc);

		for each (auto str in mats)
		{
			D3DXHANDLE handle = m_effect->GetParameterByName(NULL, str.c_str());
			if (handle)
			{
				if (str == std::string("WorldMat"))
					m_effect->SetMatrix(handle, &m_WorldMat);
				else if (str == std::string("ViewMat"))
					m_effect->SetMatrix(handle, &m_ViewMat);
				else if (str == std::string("ProjMat"))
					m_effect->SetMatrix(handle, &m_ProjMat);
				else if (str == std::string("InvWMat"))
					m_effect->SetMatrix(handle, &m_InvWorldMat);
				else if (str == std::string("InvVMat"))
					m_effect->SetMatrix(handle, &m_InvViewMat);
				else if (str == std::string("InvPMat"))
					m_effect->SetMatrix(handle, &m_InvProjMat);
				else if (str == std::string("WVMat"))
					m_effect->SetMatrix(handle, &m_WorldViewMat);
				else if (str == std::string("WVPMat"))
					m_effect->SetMatrix(handle, &m_WorldViewProjMat);
				else if (str == std::string("InvWVMat"))
					m_effect->SetMatrix(handle, &m_InvWorldViewMat);
				else if (str == std::string("InvWVPMat"))
					m_effect->SetMatrix(handle, &m_InvWorldViewProjdMat);
			}
		}

		for (int i = 0; i < texs.size(); ++i)
		{
			D3DXHANDLE handle = m_effect->GetParameterByName(NULL, texs[i]._name.c_str());
			if (handle)
			{
				hr = m_effect->SetTexture(handle, d3dtexs[i]);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	if (nIDEvent == m_timerIndex)
	{
		m_d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 198), 1.0f, 0);

		if (SUCCEEDED(m_d3d9Device->BeginScene()))
		{
			Draw();
			m_d3d9Device->EndScene();
		}
	}
	m_d3d9Device->Present(NULL, NULL, NULL, NULL);
}

int CD3D9DockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CDockablePane::OnCreate(lpCreateStruct))
		return -1;

	InitDirect9();
	SetTimer(m_timerIndex, 20, NULL);

	return 0;
}

void CD3D9DockWnd::LoadMaterial()
{
	texs.clear();
	mats.clear();

	for each (auto tex in d3dtexs)
		tex->Release();
	d3dtexs.clear();

	TiXmlDocument *_myDocument = new TiXmlDocument("Default.xml");
	_myDocument->LoadFile();

	TiXmlElement *_RootElement = _myDocument->RootElement();

	if (_RootElement == NULL)
		return;

	TiXmlElement *ChildElem = _RootElement->FirstChildElement();
	while (ChildElem)
	{
		CString text = CString(ChildElem->Value());
		if (text == CString("Textures"))
		{
			TiXmlNode* texNode = ChildElem->FirstChild();
			while (texNode)
			{
				TexUnit unit;
				unit._name = texNode->Value();
				unit._name += "Tex";
				unit._path = texNode->FirstChild()->Value();
				texs.push_back(unit);
				
				LPDIRECT3DTEXTURE9 texture;
				D3DXCreateTextureFromFileA(m_d3d9Device, unit._path.c_str(), &texture);
				d3dtexs.push_back(texture);

				texNode = texNode->NextSibling();
			}
		}
		else if (text == CString("Matrix"))
		{
			TiXmlNode* matNode = ChildElem->FirstChild();
			while (matNode)
			{
				std::string matName = matNode->Value();
				mats.push_back(matName);
				matNode = matNode->NextSibling();
			}
		}
		else if (text == CString("Effect"))
		{
			TiXmlNode* codeNode = ChildElem->FirstChild();
			LPD3DXBUFFER pCode = NULL;
// 			if (FAILED(D3DXCreateEffect(m_d3d9Device, codeNode, strlen(codeNode->Value()),
// 				NULL, NULL, D3DXFX_DONOTSAVESTATE, NULL, &m_effect, &pCode)))
// 			{
// 				LPVOID pBufPtr = pCode->GetBufferPointer();
// 				char* ErrInfo = (char*)pBufPtr;
// 				MessageBoxA(NULL, ErrInfo,"Effect error", MB_OK);
// 				pCode->Release();
// 			}

			if (FAILED(D3DXCreateEffectFromFile(m_d3d9Device, _T("TestFile.hlsl"),
				NULL, NULL, 0, NULL, &m_effect, &pCode)))
			{
				LPVOID pBufPtr = pCode->GetBufferPointer();
				char* ErrInfo = (char*)pBufPtr;
				MessageBoxA(NULL, ErrInfo, "Effect error", MB_OK);
				pCode->Release();
			}
#ifdef DEBUG
			CString code = CString(codeNode->Value());
#endif
		}
		ChildElem = ChildElem->NextSiblingElement();
	}

	return;
}