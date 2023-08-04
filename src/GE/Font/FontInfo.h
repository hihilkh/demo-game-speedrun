#pragma once

#include <string>

namespace GE::Font
{
	struct FontInfo
	{
		std::string fontName;
		int fontSize;

		FontInfo(std::string fontName, int fontSize) :
			fontName(fontName),
			fontSize(fontSize)
		{
		}

		std::string ToString() const
		{
			return fontName + "_" + std::to_string(fontSize);
		}
	};
}