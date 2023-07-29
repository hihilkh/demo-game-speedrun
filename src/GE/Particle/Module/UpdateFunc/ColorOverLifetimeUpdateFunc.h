#pragma once

namespace GE
{
	class GameObject;
}

namespace GE::Particle
{
	class ColorOverLifetimeModule;
}

namespace GE::Render
{
	class Image;
}

namespace GE::Particle::Internal
{
	class ColorOverLifetimeUpdateFunc
	{
	public:
		ColorOverLifetimeUpdateFunc(const ColorOverLifetimeModule& colorOverLifetimeModule, Render::Image& image);

		void operator()(GameObject& gameObject, float normalizedLifetime);

	private:
		const ColorOverLifetimeModule& colorOverLifetimeModule;
		Render::Image& image;
	};
}