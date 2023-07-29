#pragma once

#include "Module.h"
#include "GE/DataType/Color.h"
#include "GE/Utils/Easing.h"

namespace GE::Particle
{
	class ColorOverLifetimeModule : public Module
	{
	public:
		explicit ColorOverLifetimeModule();

		void SetColor(const Color& from, const Color& to, Easing::Type easingType);
		Color GetColor(float normalizedLifetime) const;

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) override;

	private:
		Color from;
		Color to;
		Easing::Type easingType;
	};
}