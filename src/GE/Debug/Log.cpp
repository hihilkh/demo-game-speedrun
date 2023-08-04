#include "Log.h"

#if DEBUG_IS_ENABLED(DEBUG_CONSOLE_LOGGING)

#include <windows.h>

namespace GE::Debug::Logging
{
	void Print(const char* message)
	{
		OutputDebugString(message);
	}
}

#endif