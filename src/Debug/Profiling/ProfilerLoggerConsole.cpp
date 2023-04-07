#include "ProfilerLoggerConsole.h"
#include "Utils/Log.h"
#include <iomanip>

namespace Debug::Profiler
{
	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		for (auto& section : sections) {
			Print(section->GetName() << " : " 
				<< std::fixed << std::setprecision(2)
				<< "Avg : " << section->GetCacheAvg() << " , "
				<< "Max : " << section->GetCacheMax() << " , "
				<< "Min : " << section->GetCacheMin());
		}
	}
}