#include "Image.h"
#include "GE/Render/Texture.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"

namespace GE::Render
{
	Image::Image(GameObject& gameObject, const std::string& filePath, const Color& color) :
		Renderer(gameObject),
		texture(Texture::GetTexture(filePath)),
		srcRect(RectPixel({ 0, 0 }, texture->GetSize())),
		scale({ 1.0f, 1.0f }),
		color(color)
	{
	}

	Image::Image(GameObject& gameObject, const std::string& filePath, const RectPixel& srcRect, const Color& color) :
		Renderer(gameObject),
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

	void Image::Render()
	{
		Vector2 imageSize = GetImageSize();
		auto transformData = gameObject.Transform().GetWorldTransformData();
		RectPixel drawRect(transformData.pos - imageSize / 2.0f, imageSize);
		texture->Rotate(transformData.rot, imageSize / 2.0f);
		texture->Draw(drawRect, srcRect, color);
	}
}