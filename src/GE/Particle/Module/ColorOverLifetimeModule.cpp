#include "ColorOverLifetimeModule.h"
#include "GE/Core/GameObject.h"
#include "UpdateFunc/ColorOverLifetimeUpdateFunc.h"
#include "GE/Particle/Internal/ParticleComponent.h"
#include "GE/Render/Image.h"
#include "GE/Debug/Log.h"
#include <string>

namespace GE::Particle
{
	namespace
	{
		const std::string fromNode = "from";
		const std::string toNode = "to";
		const std::string easingTypeNode = "easing_type";
	}

	ColorOverLifetimeModule::ColorOverLifetimeModule(const GE::Json::Value& json) :
		from(JsonHelper::ConvertToColor(json[fromNode])),
		to(JsonHelper::ConvertToColor(json[toNode])),
		easingType(static_cast<Easing::Type>(json[easingTypeNode].asInt()))
	{
	}

	void ColorOverLifetimeModule::ApplyModule(Internal::ParticleComponent& particleComponent) const
	{
		auto image = particleComponent.gameObject.GetComponent<Render::Image>();
		if (!image) {
			DEBUG_LOG_ERROR("なぜかParticleのImageが見つけられない。");
			return;
		}

		particleComponent.AddUpdateFunc(Internal::ColorOverLifetimeUpdateFunc(*this, *image));
	}

	Color ColorOverLifetimeModule::GetColor(float normalizedLifetime) const
	{
		float easedValue = Easing::Ease(normalizedLifetime, easingType);
		return Color::Lerp(from, to, easedValue);
	}
}

