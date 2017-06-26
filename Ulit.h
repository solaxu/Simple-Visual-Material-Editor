#pragma once

#include "stdafx.h"


namespace ShaderEditor
{
	template<typename T>
	static void SafeReleaseCOM(T& pCOM)
	{
		if (pCOM)
		{
			pCOM->Release();
			pCOM = NULL;
		}
	}
}