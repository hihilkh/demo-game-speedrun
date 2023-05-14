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
		void Draw(const RectPixel& draw, const RectPixel& src, const Color& color = Color::white) const;

	private:
		std::unique_ptr<TextureImpl> pImpl;

	private:
		explicit Texture(const std::string& filePath);
	};
}