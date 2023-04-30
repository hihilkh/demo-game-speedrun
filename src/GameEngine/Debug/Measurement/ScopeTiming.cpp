#include "GEHeader.h"
#include "ScopeTiming.h"

#if DEBUG_IS_ENABLED(DEBUG_MEASUREMENT)

#include "Debug/Log.h"

namespace Debug::Measurement
{
	ScopeTiming::ScopeTiming(const std::string& title) :
		title(title),
		startTime(std::chrono::high_resolution_clock::now())
	{
	}

	ScopeTiming::~ScopeTiming()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto microsecond = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);

		DEBUG_LOG(title << "：かかった時間：" << microsecond.count() << " microseconds");
	}
}

#endif