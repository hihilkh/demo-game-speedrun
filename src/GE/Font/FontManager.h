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
		static std::shared_ptr<Font> GetFont(const FontInfo& fontInfo);

	private:
		static std::unordered_map<std::string, std::weak_ptr<Font>> fontMap;
	};
}