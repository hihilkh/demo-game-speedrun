#pragma once

#ifdef _DEBUG

#include <sstream>
#include <windows.h>

#else

#endif // _DEBUG

namespace Log {

#ifdef _DEBUG

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

#endif // _DEBUG

}