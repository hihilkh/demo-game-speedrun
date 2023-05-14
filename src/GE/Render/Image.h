#pragma once

#include "Renderer.h"
#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include "GE/DataType/Color.h"

namespace GE::Render
{
	class Texture;

	class Image : public Renderer
	{
	public:
		Image(
			GameObject& gameObject, 
			const std::string& filePath, 
			const RectPixel& srcRect, 
			const Color& color = Color::white);

	protected:
		void Render() override;

	private:
		std::shared_ptr<Texture> texture;
		RectPixel srcRect;
		Color color;
	};
}