#include "VelocityModule.h"
#include "GE/Utils/Math.h"
#include "UpdateFunc/VelocityUpdateFunc.h"
#include "GE/Particle/Internal/ParticleComponent.h"

namespace GE::Particle
{
	VelocityModule::VelocityModule() :
		Module(),
		emitAngleRange(),
		emitSpeedRange(),
		acceleration()
	{
	}

	void VelocityModule::ApplyModule(Internal::ParticleComponent& particleComponent)
	{
		float randomEmitAngle = Math::GetRandom(emitAngleRange.x, emitAngleRange.y);
		float randomEmitSpeed = Math::GetRandom(emitSpeedRange.x, emitSpeedRange.y);

		Vector2 initialVelocity(randomEmitSpeed, 0.0f);
		initialVelocity.Rotate(randomEmitAngle);

		particleComponent.AddUpdateFunc(Internal::VelocityUpdateFunc(*this, initialVelocity));
	}
}

