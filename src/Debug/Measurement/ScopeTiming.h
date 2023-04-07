#pragma once

#include "Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_MEASUREMENT)

#include <chrono>

namespace Debug::Measurement
{
	// 参考：https://www.youtube.com/watch?v=oEx5vGNFrLk&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=63
	class ScopeTiming
	{
	public:
		explicit ScopeTiming(const std::string& title);
		~ScopeTiming();

	private:
		std::string title;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	};
}

// 備考：変数名が指定されたので、スコープによって一つの DEBUG_MEASURE_SCOPE_TIME() をしか呼び出さない
#define DEBUG_MEASURE_SCOPE_TIME(title) Debug::Measurement::ScopeTiming scopeTiming = Debug::Measurement::ScopeTiming(title)

#else

#define DEBUG_MEASURE_SCOPE_TIME(title)

#endif