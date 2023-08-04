#pragma once

#include <memory>
#include <unordered_map>
#include "FontType.h"

namespace GE::Font
{
	class Font;
	struct FontInfo;
}

namespace Lang
{
	class LanguageManager
	{
	public:
		static const FontType defaultFontType;

	public:
		static std::shared_ptr<GE::Font::Font> GetFont(FontType fontType);
		static GE::Font::FontInfo GetFontInfo(FontType fontType);
	};
}