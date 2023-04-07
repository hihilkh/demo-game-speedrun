#include "ProfilerLoggerConsole.h"
#include "Utils/Log.h"

namespace Debug::Profiler
{
	unsigned int ProfilerLoggerConsole::GetSampleSize() const
	{
		//return 1;
		return 30;
	}

	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		//for (auto& section : sections) {
		//	Print(section->GetName() << " : " << section->GetLastCache());
		//}

		for (auto& section : sections) {
			Print(section->GetName() << " : " 
				<< "Avg : " << section->GetCacheAvg() << " , "
				<< "Max : " << section->GetCacheMax() << " , "
				<< "Min : " << section->GetCacheMin());
		}
	}
}