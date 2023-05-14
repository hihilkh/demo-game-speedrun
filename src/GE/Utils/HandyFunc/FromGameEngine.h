#pragma once

#include <string>

namespace GE
{
	struct GEConfig;

	const GEConfig& GetGEConfig();
	void LoadScene(const std::string& sceneName);
}