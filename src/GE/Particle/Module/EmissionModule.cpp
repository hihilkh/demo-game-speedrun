#include "EmissionModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"
#include "GE/Particle/Internal/ParticleComponent.h"

namespace GE::Particle
{
	EmissionModule::EmissionModule() :
		Module(),
		rotRange()
	{
	}

	void EmissionModule::ApplyModule(Internal::ParticleComponent& particleComponent)
	{
		float randomRot = Math::GetRandom(rotRange.x, rotRange.y);
		particleComponent.gameObject.GetTransform().SetRot(randomRot);
	}
}

