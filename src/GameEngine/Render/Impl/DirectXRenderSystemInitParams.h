#pragma once

#include "Utils/PreprocessorDef.h"

#if _RENDERER == RENDERER_DIRECT_X

#include <windows.h>

namespace GE::Render
{
	struct RenderSystemInitParams
	{
		HWND hWnd;
	};
}

#endif