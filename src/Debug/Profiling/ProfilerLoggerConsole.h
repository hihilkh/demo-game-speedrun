#pragma once

#include "ProfilerLogger.h"

namespace Debug::Profiler
{
	class ProfilerLoggerConsole : public ProfilerLogger
	{
	public:
		~ProfilerLoggerConsole() = default;

		unsigned int GetSampleSize() const override;
		void Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;
	};
}