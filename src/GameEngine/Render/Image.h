#pragma once

#include "Renderer.h"
#include <string>
#include <memory>
#include "Utils/TypeDef.h"
#include "DataType/Rect.h"
#include "DataType/Color.h"

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