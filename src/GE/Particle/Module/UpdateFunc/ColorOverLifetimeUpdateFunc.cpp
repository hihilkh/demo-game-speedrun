#include "ColorOverLifetimeUpdateFunc.h"
#include "../ColorOverLifetimeModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Render/Image.h"

namespace GE::Particle::Internal
{
	ColorOverLifetimeUpdateFunc::ColorOverLifetimeUpdateFunc(const ColorOverLifetimeModule& colorOverLifetimeModule, Render::Image& image) :
		colorOverLifetimeModule(colorOverLifetimeModule),
		image(image)
	{
	}

	void ColorOverLifetimeUpdateFunc::operator()(GameObject& gameObject, float normalizedLifetime)
	{
		Color currentColor = colorOverLifetimeModule.GetColor(normalizedLifetime);
		image.SetColor(currentColor);
	}
}