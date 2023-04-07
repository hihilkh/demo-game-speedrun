#include "ProfilerLoggerCsv.h"
#include <filesystem>
#include <time.h>

namespace Debug::Profiler
{
	namespace
	{
		const std::string logFileFolderPath = "./profiling/";
		const char* logFileTimeFormat = "_%Y%m%d_%H%M%S";
		const std::string logFileExtension = ".csv";
	}

	ProfilerLoggerCsv::ProfilerLoggerCsv()
	{
		// 現時点を取る
		std::time_t t = std::time(nullptr);
		std::tm* tm = std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(tm, logFileTimeFormat);
		startTimeStr = oss.str();

		// フォルダを確保
		std::filesystem::create_directories(logFileFolderPath);
	}

	void ProfilerLoggerCsv::BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		// タイトル
		for (auto& section : sections) {
			LogToFile(GetLogFilePath(*section), "Avg", "Max", "Min");
		}
	}

	void ProfilerLoggerCsv::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		for (auto& section : sections) {
			LogToFile(GetLogFilePath(*section),
				section->GetCacheAvg() , 
				section->GetCacheMax(),
				section->GetCacheMin());
		}
	}

	std::string ProfilerLoggerCsv::GetLogFilePath(const ProfilerSection& section) const
	{
		return logFileFolderPath + section.GetName() + startTimeStr + logFileExtension;
	}
}