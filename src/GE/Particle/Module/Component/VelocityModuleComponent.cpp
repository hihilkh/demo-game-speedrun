#include "VelocityModuleComponent.h"
#include "../VelocityModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Transform2D.h"
#include "GE/Core/Time.h"

namespace GE::Particle::Internal
{
	VelocityModuleComponent::VelocityModuleComponent(GameObject& gameObject, const VelocityModule& velocityModule, const Vector2& initialVelocity) :
		Component(gameObject),
		velocityModule(velocityModule),
		currentVelocity(initialVelocity)
	{
	}

	void VelocityModuleComponent::Update()
	{
		Transform2D& transform = gameObject.GetTransform();
		transform.SetPos(transform.GetPos() + currentVelocity);

		currentVelocity += velocityModule.GetAcceleration() * Time::GetDeltaTime();
	}
}