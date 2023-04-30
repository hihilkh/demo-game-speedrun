#pragma once

#include "GEConfig.h"

namespace GE
{
	const GEConfig& GetGEConfig();
	void LoadScene(class Scene&& scene);
}