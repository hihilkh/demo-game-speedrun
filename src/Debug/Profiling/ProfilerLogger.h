#pragma once

#include <vector>
#include <memory>
#include "ProfilerSection.h"

namespace Debug::Profiler
{
	class ProfilerLogger
	{
	public:
		virtual ~ProfilerLogger() = default;

		virtual void BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections) {}
		virtual void Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections) = 0;
		virtual void EndLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections) {}
	};
}