#pragma once

#include "ProfilerSection.h"
#include <chrono>

namespace Debug::Profiler
{
	class ProfilerSectionFps : public ProfilerSection
	{
	public:
		ProfilerSectionFps();
		~ProfilerSectionFps();

		void Update() override;
		void ResetCaches() override;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
	};
}