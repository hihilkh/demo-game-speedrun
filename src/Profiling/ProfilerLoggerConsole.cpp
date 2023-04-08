#include "ProfilerLoggerConsole.h"
#include "Utils/Log.h"
#include <iomanip>

namespace Profiling
{
	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		for (auto& section : sections) {
			PrintSameLine(
				section->GetName() << " : " << 
				std::fixed << std::setprecision(2) << section->GetCacheAvg() << " ; ");
		}

		PrintSameLine("\n");
	}
}