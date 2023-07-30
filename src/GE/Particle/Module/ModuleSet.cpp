#include "ModuleSet.h"
#include "Module.h"

namespace GE::Particle
{
	void ModuleSet::AddModule(std::unique_ptr<Module> particleModule)
	{
		modules.emplace_back(std::move(particleModule));
	}

	void ModuleSet::ApplyModules(Internal::ParticleComponent& particleComponent) const
	{
		for (auto& particleModule : modules) {
			particleModule->ApplyModule(particleComponent);
		}
	}
}