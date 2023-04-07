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
		auto microsecond = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrameTime);
		long long microsecondInt = microsecond.count();
		if (microsecondInt == 0) {
			microsecondInt = 1;
		}

		// 整数を戻る
		long long fps = 1000000 / microsecondInt;
		AddCache(static_cast<float>(fps));

		lastFrameTime = std::chrono::high_resolution_clock::now();
	}

	void ProfilerSectionFps::ResetCaches()
	{
		ProfilerSection::ResetCaches();

		// ログでかかった時間を除く
		lastFrameTime = std::chrono::high_resolution_clock::now();
	}

	float ProfilerSectionFps::GetCacheAvg() const
	{
		// 整数を戻る
		return floor(ProfilerSection::GetCacheAvg());
	}
}