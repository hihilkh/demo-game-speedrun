#pragma once

#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "FontInfo.h"
#include "GE/UI/TextAlignment.h"

namespace GE::Font
{
	class Font
	{
		friend class FontManager;

	public:
		struct FontImpl
		{
			virtual ~FontImpl() = default;
			virtual void ShowText(
				const std::string& text, 
				const RectPixel& rect, 
				const Color& color,
				UI::TextVerticalAlignment verticalAlignment,
				UI::TextHorizontalAlignment horizontalAlignment) const = 0;
		};

	public:
		void ShowText(
			const std::string& text, 
			const RectPixel& rect,
			const Color& color,
			UI::TextVerticalAlignment verticalAlignment,
			UI::TextHorizontalAlignment horizontalAlignment) const { 
			pImpl->ShowText(text, rect, color, verticalAlignment, horizontalAlignment);
		}

	private:
		std::unique_ptr<FontImpl> pImpl;

	private:
		Font(const FontInfo& fontInfo);
	};
}