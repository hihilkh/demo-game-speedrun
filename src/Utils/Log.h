#pragma once

// TODO : このファイルをDebugフォルダーへ移す
// TODO : コードスタンダードに合わせるように
#include "Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_CONSOLE_LOGGING)

#include <sstream>
#include <windows.h>

#define PrintSameLine(message) {\
	std::stringstream ss;\
	ss << message;\
	OutputDebugString(ss.str().c_str());\
}

#define Print(message)\
	PrintSameLine(message);\
	OutputDebugString("\n")

#define PrintWarningSameLine(message)	PrintSameLine("!! : " << message)
#define PrintWarning(message)			Print("!! : " << message)

#else

#define PrintSameLine(message)
#define Print(message)
#define PrintWarningSameLine(message)
#define PrintWarning(message)

#endif