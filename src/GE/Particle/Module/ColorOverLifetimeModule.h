#pragma once

#include "Module.h"
#include "GE/DataType/Color.h"
#include "GE/Utils/Easing.h"
#include "JsonHelper.h"

namespace GE::Particle
{
	class ColorOverLifetimeModule : public Module
	{
	public:
		explicit ColorOverLifetimeModule(const GE::Json::Value& json);

		Color GetColor(float normalizedLifetime) const;

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) const override;

	private:
		Color from;
		Color to;
		Easing::Type easingType;
	};
}