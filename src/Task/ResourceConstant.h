#pragma once

#include <string>
#include <myLib.h>

// TODO : このように資料を集めることはよくないかもしれない。変更があれば、たくさんのファイルをリコンパイルになる。
namespace ResourceConstant
{

#pragma region Folders

	const std::string ImageFolder = "./data/Image/";
	const std::string MapFolder = "./data/Map/";

#pragma endregion

#pragma region Image Files

	const std::string WhiteImage = "White.png";
	const std::string ArrowImage = "Arrow.png";

	const std::string TitleImage = "Title.png";
	const std::string EndingImage = "Ending.bmp";

	// マップ
	const std::string MapImage = "MapChip.png";
	const int MapChipSize = 32;
	const ML::Point MapChipOffset = ML::Point(-16, -16);

	// マップオブジェクト
	const std::string GoalImage = "Flag.png";

	// プレイヤー
	const std::string PlayerImage = "Chara01.png";
	const std::string PlayerShadowImage = "Shadow.png";
	const int PlayerImageWidth = 32;
	const int PlayerImageHeight = 32;
	const ML::Box2D PlayerShadowSrc = ML::Box2D(0, 0, 16, 8);

	// パーティクルシステム
	const std::string WallFragmentImage = "WallFragment.png";

#pragma endregion

#pragma region Map Files

	const std::string MapFileNamePrefix = "Map";
	const std::string MapFileNameExtension = ".txt";

#pragma endregion
}