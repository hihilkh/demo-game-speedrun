#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace GE::Font
{
	class Font;
	struct FontInfo;

	class FontManager
	{
	public:
		/// <summary>
		/// 既存のFontを戻す。既存のFontがないなら、新規作成してから戻す。
		/// </summary>
		static std::shared_ptr<Font> GetFont(const FontInfo& fontInfo);

	private:
		static std::unordered_map<std::string, std::weak_ptr<Font>> fontMap;
	};
}