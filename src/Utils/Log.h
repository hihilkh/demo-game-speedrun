#pragma once

#ifdef _DEBUG

#include <sstream>
#include <windows.h>

#else

#endif // _DEBUG

namespace Log {

#ifdef _DEBUG

	#define PrintSameLine(message)\
		std::stringstream ss;\
		ss << message;\
		OutputDebugString(ss.str().c_str())

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

#endif // _DEBUG

}