#include "ParticleComponent.h"
#include "../CoreConfig.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Time.h"
#include "GE/Utils/Math.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"

namespace GE::Particle::Internal
{
	ParticleComponent::ParticleComponent(GameObject& gameObject, const CoreConfig& coreConfig) :
		Component(gameObject),
		coreConfig(coreConfig),
		startTime(Time::GetTime())
	{
	}

	void ParticleComponent::Update()
	{
		float normalizedLifetime = 0;
		if (coreConfig.life <= 0) {
			normalizedLifetime = 1;
		} else {
			normalizedLifetime = Time::GetTime() - startTime / coreConfig.life;
			Math::Clamp01(normalizedLifetime);
		}

		for (auto& updateFunc : updateFuncArray) {
			updateFunc(gameObject, normalizedLifetime);
		}

		if (normalizedLifetime >= 1) {
			Destroy(gameObject);
		}
	}
}