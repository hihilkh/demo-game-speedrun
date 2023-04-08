#include "ProfilerLoggerConsole.h"
#include "Utils/Log.h"
#include <iomanip>

namespace Profiling
{
	namespace
	{
		const std::string logPrefix = "Profiler : ";
	}

	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		PrintSameLine(logPrefix);
		for (auto& section : sections) {
			PrintSameLine(
				section->GetName() << " : " << 
				std::fixed << std::setprecision(2) << section->GetCacheAvg() << " ; ");
		}

		PrintSameLine("\n");
	}

	void ProfilerLoggerConsole::InsertMessage(const std::string& message)
	{
		Print(logPrefix << message);
	}
}