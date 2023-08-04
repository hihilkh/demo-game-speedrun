#pragma once

#include <jsoncpp/json/json.h>
#include <string>

namespace GE::Json
{
	using Value = ::Json::Value;

	Json::Value LoadJson(const std::string& file);
}