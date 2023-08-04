#pragma once

#include "ProfilerLogger.h"

namespace GE::Profiling
{
	class ProfilerLoggerConsole : public ProfilerLogger
	{
	public:
		void Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;
		void InsertMessage(const std::string& message) override;
	};
}