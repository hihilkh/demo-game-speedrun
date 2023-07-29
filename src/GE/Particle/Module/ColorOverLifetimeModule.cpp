#include "ColorOverLifetimeModule.h"
#include "GE/Core/GameObject.h"
#include "UpdateFunc/ColorOverLifetimeUpdateFunc.h"
#include "GE/Particle/Internal/ParticleComponent.h"
#include "GE/Render/Image.h"
#include "GE/Debug/Log.h"

namespace GE::Particle
{
	ColorOverLifetimeModule::ColorOverLifetimeModule() :
		from(),
		to(),
		easingType(static_cast<Easing::Type>(0))
	{
	}

	void ColorOverLifetimeModule::ApplyModule(Internal::ParticleComponent& particleComponent)
	{
		auto image = particleComponent.gameObject.GetComponent<Render::Image>();
		if (!image) {
			DEBUG_LOG_ERROR("なぜかParticleのImageが見つけられない。");
			return;
		}

		particleComponent.AddUpdateFunc(Internal::ColorOverLifetimeUpdateFunc(*this, *image));
	}

	void ColorOverLifetimeModule::SetColor(const Color& from, const Color& to, Easing::Type easingType)
	{
		this->from = from;
		this->to = to;
		this->easingType = easingType;
	}

	Color ColorOverLifetimeModule::GetColor(float normalizedLifetime) const
	{
		float easedValue = Easing::Ease(normalizedLifetime, easingType);
		return Color::Lerp(from, to, easedValue);
	}
}

