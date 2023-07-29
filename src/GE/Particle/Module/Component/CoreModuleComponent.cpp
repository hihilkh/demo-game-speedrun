#include "CoreModuleComponent.h"
#include "../CoreModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Time.h"
#include "GE/Utils/Math.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"

namespace GE::Particle::Internal
{
	CoreModuleComponent::CoreModuleComponent(GameObject& gameObject, const CoreModule& coreModule) :
		Component(gameObject),
		coreModule(coreModule),
		startTime(Time::GetTime()),
		normalizedLifetime(0.0f)
	{
		normalizedLifetime = coreModule.GetLife() > 0.0f ? 0.0f : 1.0f;
	}

	void CoreModuleComponent::Update()
	{
		if (normalizedLifetime < 1) {
			normalizedLifetime = Time::GetTime() - startTime / coreModule.GetLife();
			Math::Clamp01(normalizedLifetime);
		}

		if (normalizedLifetime >= 1) {
			Destroy(gameObject);
		}
	}
}