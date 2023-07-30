#include "RectEmissionModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"
#include "GE/Particle/Internal/ParticleComponent.h"

namespace GE::Particle
{
	RectEmissionModule::RectEmissionModule(const GE::Json::Value& json) :
		EmissionModule(json),
		rect(JsonHelper::ConvertToRect(json))
	{
	}

	void RectEmissionModule::ApplyModule(Internal::ParticleComponent& particleComponent) const
	{
		EmissionModule::ApplyModule(particleComponent);

		float randomX = Math::GetRandom(rect.x, rect.OppositeX());
		float randomY = Math::GetRandom(rect.y, rect.OppositeY());

		particleComponent.gameObject.GetTransform().SetPos(randomX, randomY);
	}
}

