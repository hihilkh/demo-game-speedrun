#pragma once

#include <string>
#include "GE/DataType/Color.h"

namespace GE
{
	struct GEConfig
	{
		std::string windowClassName = "GameEngine";
		std::string windowTitle = "Game";

		int screenWidth = 960;
		int screenHeight = 540;

		int targetFps = 60;

		Color bgColor = Color::black;
	};
}