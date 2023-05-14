#pragma once

#include "Utils/PreprocessorDef.h"

#if _PLATFORM == PLATFORM_WINDOWS

#include <windows.h>

namespace GE
{
	struct MainProgramInitParams
	{
		HINSTANCE hInstance;
		int nCmdShow;
	};
}

#endif