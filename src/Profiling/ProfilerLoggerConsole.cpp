#include "ProfilerLoggerConsole.h"
#include "Debug/Log.h"
#include <iomanip>

namespace Profiling
{
	namespace
	{
		const std::string logPrefix = "Profiler : ";
	}

	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		DEBUG_LOG_SAME_LINE(logPrefix);
		for (auto& section : sections) {
			DEBUG_LOG_SAME_LINE(
				section->GetName() << " : " << 
				std::fixed << std::setprecision(2) << section->GetCacheAvg() << " ; ");
		}

		DEBUG_LOG_SAME_LINE("\n");
	}

	void ProfilerLoggerConsole::InsertMessage(const std::string& message)
	{
		DEBUG_LOG(logPrefix << message);
	}
}