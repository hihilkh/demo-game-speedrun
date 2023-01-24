#pragma once

#if _DEBUG
#include <sstream>
#include <windows.h>
#endif

namespace Log {

#if _DEBUG

	#define Print(message)\
	{\
		std::stringstream ss;\
		ss << message << "\n";\
		OutputDebugString(ss.str().c_str());\
	}

	#define PrintWarning(message)\
	{\
		std::stringstream ss;\
		ss << "!! : " << message << "\n";\
		OutputDebugString(ss.str().c_str());\
	}

#else

	#define Print(message)
	#define PrintWarning(message)

#endif

}