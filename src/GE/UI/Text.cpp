#include "Text.h"
#include "GE/Font/FontManager.h"
#include "GE/Font/Font.h"
#include "GE/DataType/Rect.h"
#include "GE/Core/Transform2D.h"
#include "GE/Debug/Log.h"

namespace GE::UI
{
	Text::Text(GameObject& gameObject, std::shared_ptr<GE::Font::Font> font, const Vector2Int& labelSize) :
		Renderer(gameObject, 0, RenderLayer::ui),
		text(""),
		font(font),
		labelSize(labelSize),
		color(Color::black),
		verticalAlignment(TextVerticalAlignment::Middle),
		horizontalAlignment(TextHorizontalAlignment::Center)
	{
	}

	void Text::Awake()
	{
		Renderer::Awake();
		SetEnable(true);
	}

	void Text::SetFont(std::shared_ptr<GE::Font::Font> font)
	{
		this->font = font;
		SetEnable(GetEnable());
	}

	void Text::SetEnable(bool isEnable)
	{
		Renderer::SetEnable(isEnable && CheckCanEnable());
	}

	bool Text::CheckCanEnable() const
	{
		if (!font) {
			DEBUG_LOG_WARNING("fontがない。Textが有効になることができない。");
			return false;
		}

		return true;
	}

	void Text::Render(const Transform2DData& viewportData) const
	{
		RectPixel drawRect = RectPixel::FromCenter(labelSize);
		drawRect.Move(viewportData.pos);
		font->ShowText(text, drawRect, color, verticalAlignment, horizontalAlignment);
	}
}