#pragma once

namespace Log {

#if _DEBUG
	#define Print(message)\
	{\
		std::stringstream ss;\
		ss << message << "\n";\
		OutputDebugString(ss.str().c_str());\
	}
#else
	#define Print(message)
#endif

#if _DEBUG
#define PrintWarning(message)\
	{\
		std::stringstream ss;\
		ss << "!! : " << message << "\n";\
		OutputDebugString(ss.str().c_str());\
	}
#else
#define PrintWarning(message)
#endif
}