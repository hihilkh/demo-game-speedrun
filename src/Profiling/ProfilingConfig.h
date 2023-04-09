#pragma once

#define PROFILER_ENABLED			0

#if PROFILER_ENABLED

namespace Profiling
{
	// Sections
	inline const bool isEnableSectionFps		= true;
	inline const bool isEnableSectionMemory		= true;
	inline const bool isEnableSectionCpu		= true;

	// Loggers
	inline const bool isEnableLoggerConsole		= true;
	inline const bool isEnableLoggerCsv			= false;

	// その他
	inline const unsigned int sampleSize = 60;
}

#endif