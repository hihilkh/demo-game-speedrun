#include "ParticleSystem.h"
#include <string>
#include "GE/Core/GameObject.h"
#include "Module/Module.h"
#include "Internal/ParticleComponent.h"

namespace GE::Particle
{
	namespace
	{
		const std::string particleInstanceName = "Particle";
	}

	ParticleSystem::ParticleSystem(GameObject& gameObject, CoreConfig& coreConfig) :
		Component(gameObject),
		coreConfig(coreConfig)
	{
	}

	void ParticleSystem::Emit(int noOfParticle) const
	{
		for (int i = 0; i < noOfParticle; ++i) {
			CreateParticleInstance();
		}
	}

	void ParticleSystem::CreateParticleInstance() const
	{
		GameObject& particle = gameObject.AddChild(particleInstanceName);

		auto& particleComponent = particle.AddComponent<Internal::ParticleComponent>(coreConfig);

		for (auto& particleModule : modules) {
			particleModule->ApplyModule(particleComponent);
		}
	}
}