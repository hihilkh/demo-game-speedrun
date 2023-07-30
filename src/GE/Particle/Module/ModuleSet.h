#pragma once

#include <vector>
#include <memory>

namespace GE::Particle
{
	namespace Internal
	{
		class ParticleComponent;
	}

	class Module;

	class ModuleSet
	{
	public:
		void AddModule(std::unique_ptr<Module> particleModule);
		void ApplyModules(Internal::ParticleComponent& particleComponent) const;

	private:
		std::vector<std::unique_ptr<Module>> modules;
	};
}