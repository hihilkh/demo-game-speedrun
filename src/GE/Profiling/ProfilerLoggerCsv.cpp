#include "ProfilerLoggerCsv.h"
#include <filesystem>
#include <time.h>
#include <fstream>
#include <iomanip>
#include "ProfilerSection.h"

namespace GE::Profiling
{
	namespace
	{
		const std::string rootFolder = "./profiling/";
		const char* timeStrFormat = "%Y%m%d_%H%M%S";
#ifdef _DEBUG
		const std::string subFolderSuffix = "_Debug/";
#else
		const std::string subFolderSuffix = "_Release/";
#endif
		const std::string fileName = "Statistic.csv";
		const char separator = ',';
	}

	ProfilerLoggerCsv::ProfilerLoggerCsv()
	{
		std::string subFolder = GetCurrentTimeStr() + subFolderSuffix;

		// フォルダを確保
		std::filesystem::create_directories(rootFolder);
		std::filesystem::create_directories(rootFolder + subFolder);

		filePath = rootFolder + subFolder + fileName;
	}

	void ProfilerLoggerCsv::BeginLog(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		// タイトル
		std::ofstream fs(filePath, std::ios_base::app);

		for (auto& section : sections) {
			fs << section->GetName() << separator;
		}
		fs << '\n';
	}

	void ProfilerLoggerCsv::Log(const std::vector<std::unique_ptr<ProfilerSection>>& sections)
	{
		std::ofstream fs(filePath, std::ios_base::app);

		fs << std::fixed << std::setprecision(2);

		for (auto& section : sections) {
			fs << section->GetCacheAvg() << separator;
		}
		fs << '\n';
	}

	void ProfilerLoggerCsv::InsertMessage(const std::string& message)
	{
		std::fstream fs(filePath);
		fs.seekp(-2, std::ios_base::end);	// 最後の行のseparatorの後へ移動する
		fs << message << separator << '\n';
	}

	std::string ProfilerLoggerCsv::GetCurrentTimeStr() const
	{
		std::time_t t = std::time(nullptr);
		std::tm* tm = std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(tm, timeStrFormat);
		return oss.str();
	}
}