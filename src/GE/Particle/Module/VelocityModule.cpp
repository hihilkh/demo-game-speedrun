#include "VelocityModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"
#include "Component/VelocityModuleComponent.h"

namespace GE::Particle
{
	VelocityModule::VelocityModule() :
		Module(),
		emitAngleRange(),
		emitSpeedRange(),
		acceleration()
	{
	}

	void VelocityModule::ApplyModule(GameObject& baseObject)
	{
		float randomEmitAngle = Math::GetRandom(emitAngleRange.x, emitAngleRange.y);
		float randomEmitSpeed = Math::GetRandom(emitSpeedRange.x, emitSpeedRange.y);

		Vector2 initialVelocity(randomEmitSpeed, 0.0f);
		initialVelocity.Rotate(randomEmitAngle);

		baseObject.AddComponent<Internal::VelocityModuleComponent>(*this, initialVelocity);
	}
}

