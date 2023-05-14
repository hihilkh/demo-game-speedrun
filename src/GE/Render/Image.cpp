#include "Image.h"
#include "GE/Render/Texture.h"

namespace GE::Render
{
	Image::Image(GameObject& gameObject, const std::string& filePath, const RectPixel& srcRect, const Color& color) :
		Renderer(gameObject),
		texture(Texture::GetTexture(filePath)),
		srcRect(srcRect),
		color(color)
	{
	}

	void Image::Render()
	{
		// TODO : GameObject / Transform　/ カメラによっての位置計算
		RectPixel drawRect(0, 0, srcRect.width, srcRect.height);
		texture->Draw(drawRect, srcRect, color);
	}
}