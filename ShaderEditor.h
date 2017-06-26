
// ShaderEditor.h : main header file for the ShaderEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CShaderEditorApp:
// See ShaderEditor.cpp for the implementation of this class
//

#pragma comment(lib, "tinyxml.lib")

class CShaderEditorApp : public CWinAppEx
{
public:
	CShaderEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CShaderEditorApp theApp;
