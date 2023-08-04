#include "Image.h"
#include "GE/Render/Texture.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"
#include "GE/Core/Camera2D.h"
#include "RenderLayer.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"
#include "GE/Core/GEConfig.h"
#include "GE/Utils/HandyFunc/CollisionRelated.h"

namespace GE::Render
{
	Image::Image(GameObject& gameObject, const std::string& filePath, const Color& color) :
		Renderer(gameObject, 0, RenderLayer::general),
		texture(Texture::GetTexture(filePath)),
		srcRect(RectPixel({ 0, 0 }, texture->GetSize())),
		scale({ 1.0f, 1.0f }),
		color(color)
	{
	}

	Image::Image(GameObject& gameObject, const std::string& filePath, const RectPixel& srcRect, const Color& color) :
		Renderer(gameObject, 0, RenderLayer::general),
		texture(Texture::GetTexture(filePath)),
		srcRect(srcRect),
		scale({ 1.0f, 1.0f }),
		color(color)
	{
	}

	Vector2 Image::GetImageSize() const
	{
		return Vector2::Scale(srcRect.size, scale);
	}

	void Image::SetImageSize(const Vector2& size)
	{
		SetScale({ size.x / srcRect.size.x, size.y / srcRect.size.y });
	}

	void Image::Render(const Transform2DData& viewportData) const
	{
		Vector2 imageSize = GetImageSize();
		RectPixel drawRect = RectPixel::FromCenter(imageSize);
		drawRect.Move(viewportData.pos);

		// カリング
		const GEConfig& config = GetGEConfig();
		Rect screenRect(0.0f, 0.0f, (float)config.screenWidth, (float)config.screenHeight);
		Collision::Detection::CollidedType collidedType = Collision::CheckCollision(screenRect, drawRect, 0.0f, viewportData.rot);
		if (collidedType != Collision::Detection::CollidedType::Overlap) {
			return;
		}

		texture->Rotate(viewportData.rot, imageSize / 2.0f);
		texture->Draw(drawRect, srcRect, color);
	}
}