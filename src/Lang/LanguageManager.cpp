#include "GE/GEHeader.h"
#include "LanguageManager.h"
#include "GE/Font/FontManager.h"
#include "GE/Font/Font.h"
#include <magic_enum.hpp>

namespace Lang
{
	using namespace GE::Font;

	const FontType LanguageManager::defaultFontType = FontType::DefaultSmall;

	std::shared_ptr<Font> LanguageManager::GetFont(FontType fontType)
	{
		FontInfo fontInfo = GetFontInfo(fontType);
		return FontManager::GetFont(fontInfo);
	}

	FontInfo LanguageManager::GetFontInfo(FontType fontType)
	{
		static const std::string msGothic = "MS ゴシック";

		static const int fontSizeSmall = 24;
		static const int fontSizeLarge = 34;

		switch (fontType) {
			case FontType::DefaultSmall:	return FontInfo(msGothic, fontSizeSmall);
			case FontType::DefaultLarge:	return FontInfo(msGothic, fontSizeLarge);
			default:
				DEBUG_LOG_WARNING("FontType : " << magic_enum::enum_name(fontType) << "のFontInfoは未定義です。デフォルトのFontTypeのFontInfoを戻す。");
				return GetFontInfo(defaultFontType);
		}
	}
}