﻿#pragma once

#include "ProfilerSection.h"
#include <windows.h>

namespace GE::Profiling
{
	// 参考：https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
	class ProfilerSectionMemory : public ProfilerSection
	{
	public:
		ProfilerSectionMemory();

		void Update(bool isLastSample) override;

	private:
		HANDLE currentProcess;
	};
}