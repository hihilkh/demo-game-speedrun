#pragma once

#include "GE/Core/Component.h"

namespace GE::Particle
{
	class CoreModule;
}

namespace GE::Particle::Internal
{
	class CoreModuleComponent : public Component
	{
	public:
		CoreModuleComponent(GameObject& gameObject, const CoreModule& coreModule);

		float GetNormalizedLifetime() const { return normalizedLifetime; }

	protected:
		void Update() override;

	private:
		const CoreModule& coreModule;
		float startTime;
		float normalizedLifetime;
	};
}