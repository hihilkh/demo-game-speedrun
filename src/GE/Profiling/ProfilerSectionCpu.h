#pragma once

#include "ProfilerSection.h"
#include <windows.h>

namespace GE::Profiling
{
	// 参考：https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
	class ProfilerSectionCpu : public ProfilerSection
	{
	public:
		ProfilerSectionCpu();

		void Update(bool isLastSample) override;

	private:
		HANDLE currentProcess;
		int noOfProcessors;

		ULONGLONG systemTimeQuad;
		ULONGLONG processKernelTimeQuad;
		ULONGLONG processUserTimeQuad;

	private:
		void GetCurrentTimes(ULONGLONG& outSystemTimeQuad, ULONGLONG& outProcessKernelTimeQuad, ULONGLONG& outProcessUserTimeQuad);
		ULONGLONG GetQuadPart(const FILETIME& fileTime) const;
		float GetCpuUsagePercent();
	};
}