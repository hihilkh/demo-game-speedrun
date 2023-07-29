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

		void ApplyModule(GameObject& baseObject) override;

		void SetColor(const Color& from, const Color& to, Easing::Type easingType);
		Color GetColor(float normalizedLifetime) const;

	private:
		Color from;
		Color to;
		Easing::Type easingType;
	};
}