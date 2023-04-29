#include "Log.h"

#if DEBUG_IS_ENABLED(DEBUG_CONSOLE_LOGGING)

#include <windows.h>

// Log.hを小さくなるために、Log.cppを使う
namespace Debug::Logging
{
	void Print(const char* message)
	{
		OutputDebugString(message);
	}
}

#endif