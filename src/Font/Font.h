#pragma once

#include <GameEngine_Ver3_83.h>

/// <summary>
/// 全般的に使われるフォントを格納する
/// </summary>
namespace Font
{
	extern int smallDefaultFontSize;
	extern DG::Font::SP smallDefaultFont;

	extern int largeDefaultFontSize;
	extern DG::Font::SP largeDefaultFont;

	void Init();
}