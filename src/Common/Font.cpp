#include "Font.h"

namespace Font
{
	namespace
	{
		const std::string DefaultFontName = "MS ゴシック";
		bool isInitialized = false;
	}

	int smallDefaultFontSize = 24;
	int largeDefaultFontSize = 40;

	DG::Font::SP smallDefaultFont;
	DG::Font::SP largeDefaultFont;

	void Init()
	{
		if (isInitialized) {
			return;
		}

		isInitialized = true;
		smallDefaultFont = DG::Font::Create(DefaultFontName, smallDefaultFontSize / 2, smallDefaultFontSize);
		largeDefaultFont = DG::Font::Create(DefaultFontName, largeDefaultFontSize / 2, largeDefaultFontSize);
	}
}