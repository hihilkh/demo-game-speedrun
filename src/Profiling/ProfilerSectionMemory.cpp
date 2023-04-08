#include "ProfilerSectionMemory.h"

#include <windows.h>
#include <psapi.h>
#include "Utils/Log.h"

namespace Profiling
{
	ProfilerSectionMemory::ProfilerSectionMemory() :
		ProfilerSection("virtual_memory_mb"),
		currentProcess(GetCurrentProcess())
	{
	}

	ProfilerSectionMemory::~ProfilerSectionMemory()
	{
	}

	void ProfilerSectionMemory::Update(bool isLastSample)
	{

		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(currentProcess, &pmc, sizeof(pmc))) {
			AddCache(pmc.PagefileUsage / 1048576.0f);	// 1048576 = 1024 * 1024
		} else {
			PrintWarning("GetProcessMemoryInfo 失敗。メモリーが取れない。");
		}
	}
}