#pragma once

#include "GE/Core/Component.h"
#include <memory>
#include <string>

namespace GE::Particle
{
	struct CoreConfig;
	class ModuleSet;

	class ParticleSystem : public Component
	{
	public:
		ParticleSystem(GameObject& gameObject, const std::string& particleSystemFile);

		void Play() const;

	private:
		std::shared_ptr<CoreConfig> coreConfig;
		std::shared_ptr<ModuleSet> moduleSet;

	private:
		void CreateParticleInstance() const;
	};
}