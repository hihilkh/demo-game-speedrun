#pragma once

#include "GE/Core/Component.h"

namespace GE::Particle
{
	class ColorOverLifetimeModule;
}

namespace GE::Particle::Internal
{
	class ColorOverLifetimeModuleComponent : public Component
	{
	public:
		ColorOverLifetimeModuleComponent(GameObject& gameObject, const ColorOverLifetimeModule& colorOverLifetimeModule);

	protected:
		void Update() override;

	private:
		const ColorOverLifetimeModule& colorOverLifetimeModule;
	};
}