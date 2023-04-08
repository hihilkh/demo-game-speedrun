#pragma once

#define PROFILER_ENABLED			1

#if PROFILER_ENABLED

namespace Profiling
{
	// Sections
	inline const bool enableSectionFps		= true;
	inline const bool enableSectionMemory	= true;
	inline const bool enableSectionCpu		= true;

	// Loggers
	inline const bool enableLoggerConsole	= true;
	inline const bool enableLoggerCsv		= false;

	// その他
	inline const unsigned int sampleSize = 60;
}

#endif