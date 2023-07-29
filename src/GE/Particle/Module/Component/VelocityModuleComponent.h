#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE::Particle
{
	class VelocityModule;
}

namespace GE::Particle::Internal
{
	class VelocityModuleComponent : public Component
	{
	public:
		VelocityModuleComponent(
			GameObject& gameObject, 
			const VelocityModule& velocityModule,
			const Vector2& initialVelocity);

	protected:
		void Update() override;

	private:
		const VelocityModule& velocityModule;
		Vector2 currentVelocity;
	};
}