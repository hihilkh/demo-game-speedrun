#include "ProfilerSectionFps.h"

namespace Debug::Profiler
{
	ProfilerSectionFps::ProfilerSectionFps() :
		ProfilerSection("fps"),
		lastFrameTime(std::chrono::high_resolution_clock::now())
	{
	}

	ProfilerSectionFps::~ProfilerSectionFps()
	{
	}

	void ProfilerSectionFps::Update(bool isLastSample)
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto microsecond = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrameTime);
		long long microsecondInt = microsecond.count();
		if (microsecondInt == 0) {
			microsecondInt = 1;
		}

		float fps = 1000000.0f / microsecondInt;
		AddCache(fps);

		lastFrameTime = std::chrono::high_resolution_clock::now();
	}

	void ProfilerSectionFps::ResetCaches()
	{
		ProfilerSection::ResetCaches();

		// ログでかかった時間を除く
		lastFrameTime = std::chrono::high_resolution_clock::now();
	}
}