#pragma once

#include "DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_CONSOLE_LOGGING)

#include <sstream>
#include <windows.h>

#define DEBUG_LOG_SAME_LINE(message) {\
	std::stringstream ss;\
	ss << message;\
	OutputDebugString(ss.str().c_str());\
}

#define DEBUG_LOG(message)						DEBUG_LOG_SAME_LINE(message << '\n');

#define DEBUG_LOG_WARNING_SAME_LINE(message)	DEBUG_LOG_SAME_LINE("!! : " << message)
#define DEBUG_LOG_WARNING(message)				DEBUG_LOG("!! : " << message)

#else

#define DEBUG_LOG_SAME_LINE(message)
#define DEBUG_LOG(message)
#define DEBUG_LOG_WARNING_SAME_LINE(message)
#define DEBUG_LOG_WARNING(message)

#endif