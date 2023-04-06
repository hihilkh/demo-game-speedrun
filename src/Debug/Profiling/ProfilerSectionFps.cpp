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

	void ProfilerSectionFps::Update()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime);
		float fps = 1000.0f / millisecond.count();
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