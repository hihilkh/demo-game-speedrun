#include "FontManager.h"
#include "Font.h"
#include <exception>
#include "GE/Debug/Log.h"

namespace GE::Font
{
	std::unordered_map<std::string, std::weak_ptr<Font>> FontManager::fontMap;

	std::shared_ptr<Font> FontManager::GetFont(const FontInfo& fontInfo)
	{
		auto findResult = fontMap.find(fontInfo.ToString());
		if (findResult != fontMap.end()) {
			if (findResult->second.expired()) {
				fontMap.erase(findResult);
			} else {
				return findResult->second.lock();
			}
		}

		struct SharedPtrEnabler : public Font
		{
			SharedPtrEnabler(const FontInfo& info) : Font(info)
			{
			}
		};

		std::shared_ptr<Font> font;
		try {
			font = std::make_shared<SharedPtrEnabler>(fontInfo);
		} catch (std::exception& ex) {
			DEBUG_LOG_WARNING(ex.what());
		}

		if (font) {
			fontMap.insert({ fontInfo.ToString(), font});
		}

		return font;
	}
}