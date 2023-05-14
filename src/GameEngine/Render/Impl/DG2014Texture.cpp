﻿#include "Utils/PreprocessorDef.h"

#if _RENDERER == RENDERER_DIRECT_X

#include "../Texture.h"
#include "DG2014/DG2014_Image.h"
#include "DataType/Rect.h"

namespace GE::Render
{
	namespace
	{
		ML::Box2D ConvertRect(const RectPixel& rect)
		{
			return ML::Box2D(rect.x, rect.y, rect.width, rect.height);
		}

		ML::Color ConvertColor(const Color& color)
		{
			return ML::Color(color.a, color.r, color.g, color.b);
		}
	}

	class TextureImpl
	{
	public:
		DG::Image::SP dgImage;

	public:
		TextureImpl(const std::string& filePath) :
			dgImage(DG::Image::Create(filePath))
		{
		}
	};

	Texture::Texture(const std::string& filePath) :
		pImpl(std::make_unique<TextureImpl>(filePath))
	{
	}

	Texture::~Texture() = default;

	// TODO : 
	// DG2014を依存しないで、自分のアセット管理システムを作る
	// (今常に新しいTextureのshared_ptrを作って、TextureImplでアセットを管理する。)
	std::shared_ptr<Texture> Texture::GetTexture(const std::string& filePath)
	{
		struct SharedPtrEnabler : public Texture {
			SharedPtrEnabler(const std::string& filePath) : Texture(filePath)
			{
			}
		};
		return std::make_shared<SharedPtrEnabler>(filePath);
	}

	void Texture::Draw(const RectPixel& draw, const RectPixel& src, const Color& color) const
	{
		// TODO : 今たくさんの無駄なConvertRectとConvertColorを呼び出す
		pImpl->dgImage->Draw(ConvertRect(draw), ConvertRect(src), ConvertColor(color));
	}
}

#endif