#include "Json.h"
#include <fstream>
#include "GE/Debug/Log.h"

namespace GE::Json
{
	Json::Value LoadJson(const std::string& file)
	{
		Json::Value returnValue;

		std::ifstream fileStream(file);
		if (!fileStream) {
			DEBUG_LOG_ERROR("ファイルの読み込みを失敗した。ファイルパス：" << file);
			return returnValue;
		}

		std::string jsonStr;
		std::getline(fileStream, jsonStr);
		fileStream.close();

		::Json::Reader reader;
		reader.parse(jsonStr, returnValue);

		return returnValue;
	}
}