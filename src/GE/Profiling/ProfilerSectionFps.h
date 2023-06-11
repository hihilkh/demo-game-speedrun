#pragma once

#include "ProfilerSection.h"
#include <chrono>

namespace GE::Profiling
{
	class ProfilerSectionFps : public ProfilerSection
	{
	public:
		ProfilerSectionFps();

		void Update(bool isLastSample) override;
		void ResetCaches() override;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
	};
}