#include "ProfilerLoggerCsv.h"
#include <filesystem>
#include <time.h>

namespace Profiling
{
	namespace
	{
		const std::string rootFolder = "./profiling/";
		const char* subFolderFormat = "%Y%m%d_%H%M%S/";
		const std::string fileName = "Result";
		const std::string fileExtension = ".csv";
	}

	ProfilerLoggerCsv::ProfilerLoggerCsv()
	{
		// 現時点を取る
		std::time_t t = std::time(nullptr);
		std::tm* tm = std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(tm, subFolderFormat);
		subFolder = oss.str();

		// フォルダを確保
		std::filesystem::create_directories(rootFolder);
		std::filesystem::create_directories(rootFolder + subFolder);
	}

	void ProfilerLoggerCsv::BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		// タイトル
		std::ofstream fs = OpenLogFile();

		for (auto& section : sections) {
			fs << section->GetName() << ',';
		}
		fs << '\n';
	}

	void ProfilerLoggerCsv::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		std::ofstream fs = OpenLogFile();

		fs << std::fixed << std::setprecision(2);

		for (auto& section : sections) {
			fs << section->GetCacheAvg() << ',';
		}
		fs << '\n';
	}

	std::ofstream ProfilerLoggerCsv::OpenLogFile() const
	{
		std::string filePath = rootFolder + subFolder + fileName + fileExtension;
		return std::ofstream(filePath, std::ios_base::app);
	}
}