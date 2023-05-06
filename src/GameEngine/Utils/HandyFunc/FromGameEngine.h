#pragma once

#include <string>
#include "Core/GEConfig.h"

namespace GE
{
	const GEConfig& GetGEConfig();
	void LoadScene(const std::string& sceneName);
}