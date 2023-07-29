#include "ColorOverLifetimeModule.h"
#include "GE/Core/GameObject.h"
#include "Component/ColorOverLifetimeModuleComponent.h"

namespace GE::Particle
{
	ColorOverLifetimeModule::ColorOverLifetimeModule() :
		from(),
		to(),
		easingType(static_cast<Easing::Type>(0))
	{
	}

	void ColorOverLifetimeModule::ApplyModule(GameObject& baseObject)
	{
		baseObject.AddComponent<Internal::ColorOverLifetimeModuleComponent>(*this);
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

