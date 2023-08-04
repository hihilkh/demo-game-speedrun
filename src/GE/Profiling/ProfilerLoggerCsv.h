#pragma once

#include "ProfilerLogger.h"

namespace GE::Profiling
{
	class ProfilerLoggerCsv : public ProfilerLogger
	{
	public:
		ProfilerLoggerCsv();

		void BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;
		void Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;
		void InsertMessage(const std::string& message) override;

	private:
		std::string filePath;

	private:
		std::string GetCurrentTimeStr() const;
	};
}