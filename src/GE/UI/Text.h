#pragma once

#include "GE/Render/Renderer.h"
#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"
#include "GE/DataType/Color.h"
#include "TextAlignment.h"

namespace GE::Font
{
	class Font;
}

namespace GE::UI
{
	class Text : public GE::Render::Renderer
	{
	public:
		Text(
			GameObject& gameObject, 
			std::shared_ptr<GE::Font::Font> font,
			const Vector2Int& labelSize);

		void SetIsEnable(bool isEnable) override;

#pragma region ゲッター/セッター

		const std::string& GetText() const { return text; }
		void SetText(const std::string& text) { this->text = text; }

		std::shared_ptr<GE::Font::Font> GetFont() const { return font; }
		void SetFont(std::shared_ptr<GE::Font::Font> font);

		const Vector2Int& GetLabelSize() const { return labelSize; }
		void SetLabelSize(const Vector2Int& labelSize) { this->labelSize = labelSize; }

		const Color& GetColor() const { return color; }
		void SetColor(const Color& color) { this->color = color; }
		
		TextVerticalAlignment GetVerticalAlignment() const { return verticalAlignment; }
		void SetVerticalAlignment(TextVerticalAlignment alignment) { verticalAlignment = alignment; }

		TextHorizontalAlignment GetHorizontalAlignment() const { return horizontalAlignment; }
		void SetHorizontalAlignment(TextHorizontalAlignment alignment) { horizontalAlignment = alignment; }

#pragma endregion

	protected:
		void Awake() override;
		void Render(const Transform2DData& viewportData) const override;

	private:
		std::string text;
		std::shared_ptr<GE::Font::Font> font;
		Vector2Int labelSize;
		Color color;

		TextVerticalAlignment verticalAlignment;
		TextHorizontalAlignment horizontalAlignment;

	private:
		bool CheckCanEnable() const;
	};
}