#pragma once

#define PROFILER_ENABLED			1

#if PROFILER_ENABLED

namespace Profiling
{
	// Sections
	inline const bool isEnableSectionFps		= true;
	inline const bool isEnableSectionMemory		= true;
	inline const bool isEnableSectionCpu		= true;

	// Loggers
	inline const bool isEnableLoggerConsole		= false;
	inline const bool isEnableLoggerCsv			= true;

	// その他
	inline const unsigned int sampleSize = 60;
}

#endif