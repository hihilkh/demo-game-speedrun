﻿#pragma once

#include "DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_CONSOLE_LOGGING)

#include <sstream>

namespace GE::Debug::Logging
{
	void Print(const char* message);
}

#define DEBUG_LOG_SAME_LINE(message) {\
	std::ostringstream ss;\
	ss << message;\
	GE::Debug::Logging::Print(ss.str().c_str());\
}

#define DEBUG_LOG(message)						DEBUG_LOG_SAME_LINE(message << '\n')

#define DEBUG_LOG_WARNING_SAME_LINE(message)	DEBUG_LOG_SAME_LINE("!! : " << message)
#define DEBUG_LOG_WARNING(message)				DEBUG_LOG("!! : " << message)

#define DEBUG_LOG_ERROR_SAME_LINE(message)		DEBUG_LOG_SAME_LINE("XXXX : " << message)
#define DEBUG_LOG_ERROR(message)				DEBUG_LOG("XXXX : " << message)
#else

#define DEBUG_LOG_SAME_LINE(message)
#define DEBUG_LOG(message)
#define DEBUG_LOG_WARNING_SAME_LINE(message)
#define DEBUG_LOG_WARNING(message)
#define DEBUG_LOG_ERROR_SAME_LINE(message)
#define DEBUG_LOG_ERROR(message)

#endif