#pragma once

#include "GE/Utils/PreprocessorDef.h"

#if _RENDERER == RENDERER_DG2014

#include <windows.h>

namespace GE::Render
{
	struct RenderSystemInitParams
	{
		HWND hWnd;
	};
}

#endif