#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE
{
	class GameObject;
}

namespace GE::Particle
{
	class VelocityModule;
}

namespace GE::Particle::Internal
{
	class VelocityUpdateFunc
	{
	public:
		VelocityUpdateFunc(const VelocityModule& velocityModule, const Vector2& initialVelocity);

		void operator()(GameObject& gameObject, float normalizedLifetime);

	private:
		const VelocityModule& velocityModule;
		Vector2 currentVelocity;
	};
}