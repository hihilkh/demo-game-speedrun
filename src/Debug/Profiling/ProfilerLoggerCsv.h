#pragma once

#include "ProfilerLogger.h"
#include <fstream>

namespace Debug::Profiler
{
	class ProfilerLoggerCsv : public ProfilerLogger
	{
	public:
		ProfilerLoggerCsv();
		~ProfilerLoggerCsv() = default;

	public:
		void BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;
		void Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections) override;

	private:
		std::string startTimeStr;

	private:
		std::string GetLogFilePath(const ProfilerSection& section) const;

		template<typename T>
		void LogToFile(const std::string& filePath, const T& avg, const T& max, const T& min) const
		{
			std::ofstream fs;
			fs.open(filePath, std::ios_base::app);
			fs	<< avg << ','
				<< max << ','
				<< min << '\n';
		}
	};
}