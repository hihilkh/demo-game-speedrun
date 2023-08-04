#pragma once

#include <memory>
#include <string>
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Color.h"

namespace GE::Render
{
	class TextureImpl;

	class Texture
	{
	public:
		~Texture();	// TextureImplが前方宣言できるために、デストラクタを宣言し、cppで定義する

		static std::shared_ptr<Texture> GetTexture(const std::string& filePath);
		Vector2Int GetSize() const;
		void Draw(const RectPixel& draw, const RectPixel& src, const Color& color = Color::white) const;

		// TODO : Textureから回転すれば、ちょっとおかしいと思う。他の方法を考える
		void Rotate(float angle, const Vector2& center) const;

	private:
		std::unique_ptr<TextureImpl> pImpl;

	private:
		explicit Texture(const std::string& filePath);
	};
}