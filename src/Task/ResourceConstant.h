#pragma once

#include <string>

namespace ResourceConstant
{

#pragma region Folders

	const std::string ImageFolder = "./data/Image/";
	const std::string MapFolder = "./data/Map/";

#pragma endregion

#pragma region Image Files

	const std::string TitleImage = "Title.bmp";
	const std::string EndingImage = "Ending.bmp";

	const std::string MapImage = "MapChip01.bmp";
	const int NoOfMapChip = 16;
	const int NoOfMapChipInRow = 8;
	const int MapChipSize = 32;

	const std::string PlayerImage = "Chara01.png";

#pragma endregion

#pragma region Map Files

	const std::string MapFileNamePrefix = "Map";
	const std::string MapFileNameExtension = ".txt";

#pragma endregion
}