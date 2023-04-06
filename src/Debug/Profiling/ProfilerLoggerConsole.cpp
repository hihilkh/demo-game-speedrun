#include "ProfilerLoggerConsole.h"
#include "Utils/Log.h"

namespace Debug::Profiler
{
	void ProfilerLoggerConsole::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		for (auto& section : sections) {
			Print(section->GetName() << " : " << section->GetLastCache());
		}
	}
}