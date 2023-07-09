#pragma once

#include "Renderer.h"
#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include "GE/DataType/Color.h"
#include "GE/DataType/Vector2.h"

namespace GE::Render
{
	class Texture;

	class Image : public Renderer
	{
	public:
		Image(
			GameObject& gameObject,
			const std::string& filePath,
			const Color& color = Color::white);

		Image(
			GameObject& gameObject, 
			const std::string& filePath, 
			const RectPixel& srcRect, 
			const Color& color = Color::white);

#pragma region ゲッター/セッター

		const RectPixel& GetSrcRect() const { return srcRect; }
		void SetSrcRect(const RectPixel& srcRect) { this->srcRect = srcRect; }

		const Vector2& GetScale() const { return scale; }
		void SetScale(const Vector2& scale) { this->scale = scale; }
		void SetUniformScale(float scale) { this->scale.x = scale; this->scale.y = scale; }

		const Color& GetColor() const { return color; }
		void SetColor(const Color& color) { this->color = color; }

		float GetAlpha() const { return color.a; }
		void SetAlpha(float alpha) { this->color.a = alpha; }

		Vector2 GetImageSize() const;
		void SetImageSize(const Vector2& size);

#pragma endregion

	protected:
		void Render(const Transform2DData& viewportData) const override;

	private:
		std::shared_ptr<Texture> texture;
		RectPixel srcRect;
		Vector2 scale;
		Color color;
	};
}