#include "ProfilerSectionCpu.h"

namespace GE::Profiling
{
	ProfilerSectionCpu::ProfilerSectionCpu() :
		ProfilerSection("CPU (%)"),
        currentProcess(GetCurrentProcess())
	{
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        noOfProcessors = sysInfo.dwNumberOfProcessors;

        GetCurrentTimes(systemTimeQuad, processKernelTimeQuad, processUserTimeQuad);
	}

	void ProfilerSectionCpu::Update(bool isLastSample)
	{
        if (!isLastSample) {
            return;
        }

        AddCache(GetCpuUsagePercent());
	}

    void ProfilerSectionCpu::GetCurrentTimes(ULONGLONG& outSystemTimeQuad, ULONGLONG& outProcessKernelTimeQuad, ULONGLONG& outProcessUserTimeQuad)
    {
        FILETIME systemTime;
        GetSystemTimeAsFileTime(&systemTime);
        outSystemTimeQuad = GetQuadPart(systemTime);

        FILETIME dummyTime, processKernelTime, processUserTime;
        GetProcessTimes(currentProcess, &dummyTime, &dummyTime, &processKernelTime, &processUserTime);
        outProcessKernelTimeQuad = GetQuadPart(processKernelTime);
        outProcessUserTimeQuad = GetQuadPart(processUserTime);
    }

    ULONGLONG ProfilerSectionCpu::GetQuadPart(const FILETIME& fileTime) const
    {
        ULARGE_INTEGER uLargeInt;
        uLargeInt.LowPart = fileTime.dwLowDateTime;
        uLargeInt.HighPart = fileTime.dwHighDateTime;

        return uLargeInt.QuadPart;
    }

    float ProfilerSectionCpu::GetCpuUsagePercent()
    {
        ULONGLONG newSystemTimeQuad, newProcessKernelTimeQuad, newProcessUserTimeQuad;
        GetCurrentTimes(newSystemTimeQuad, newProcessKernelTimeQuad, newProcessUserTimeQuad);

        ULONGLONG deltaSystemTime = newSystemTimeQuad - systemTimeQuad;
        if (deltaSystemTime == 0) {
            return 0.0f;
        }

        ULONGLONG deltaProcessTime = 
            (newProcessKernelTimeQuad - processKernelTimeQuad) +
            (newProcessUserTimeQuad - processUserTimeQuad);

        systemTimeQuad = newSystemTimeQuad;
        processKernelTimeQuad = newProcessKernelTimeQuad;
        processUserTimeQuad = newProcessUserTimeQuad;

        return deltaProcessTime * 100.0f / (deltaSystemTime * noOfProcessors);
    }
}