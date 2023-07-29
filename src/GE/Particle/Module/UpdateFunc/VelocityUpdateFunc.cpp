#include "VelocityUpdateFunc.h"
#include "../VelocityModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"
#include "GE/Core/Time.h"

namespace GE::Particle::Internal
{
	VelocityUpdateFunc::VelocityUpdateFunc(const VelocityModule& velocityModule, const Vector2& initialVelocity) :
		velocityModule(velocityModule),
		currentVelocity(initialVelocity)
	{
	}

	void VelocityUpdateFunc::operator()(GameObject& gameObject, float normalizedLifetime)
	{
		Transform2D& transform = gameObject.GetTransform();
		transform.SetPos(transform.GetPos() + currentVelocity);

		currentVelocity += velocityModule.GetAcceleration() * Time::GetDeltaTime();
	}
}