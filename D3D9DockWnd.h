#pragma once

#include "Ulit.h"
#include <d3dx9math.h>
#include <vector>
// D3D9DockWnd

struct TexUnit
{
	std::string _name;
	std::string _path;
};


class CD3D9DockWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CD3D9DockWnd)

public:
	CD3D9DockWnd();
	virtual ~CD3D9DockWnd();

public:
	LPDIRECT3D9 m_d3d9 = NULL;
	LPDIRECT3DDEVICE9 m_d3d9Device = NULL;
	LPD3DXEFFECT m_effect = NULL;

	D3DXMATRIX m_WorldMat;
	D3DXMATRIX m_ViewMat;
	D3DXMATRIX m_ProjMat;
	D3DXMATRIX m_WorldViewMat;
	D3DXMATRIX m_WorldViewProjMat;
	D3DXMATRIX m_InvWorldMat;
	D3DXMATRIX m_InvWorldViewMat;
	D3DXMATRIX m_InvWorldViewProjdMat;
	D3DXMATRIX m_InvViewMat;
	D3DXMATRIX m_InvProjMat;

	std::vector<TexUnit> texs;
	std::vector<std::string> mats;

	std::vector<LPDIRECT3DTEXTURE9> d3dtexs;

	LPD3DXMESH m_sphere = NULL;
protected:
	UINT m_timerIndex = 1;
public:

	// жиди
	virtual void Draw();
	virtual BOOL InitDirect9();

	void LoadMaterial();

protected:
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

protected:
	DECLARE_MESSAGE_MAP()
};


