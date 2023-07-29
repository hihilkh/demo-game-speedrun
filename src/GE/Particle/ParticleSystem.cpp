#include "ParticleSystem.h"
#include <string>
#include "GE/Core/GameObject.h"
#include "Module/Module.h"

namespace GE::Particle
{
	namespace
	{
		const std::string particleInstanceName = "Particle";
	}

	ParticleSystem::ParticleSystem(GameObject& gameObject) :
		Component(gameObject)
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
		for (auto& particleModule : modules) {
			particleModule->ApplyModule(particle);
		}
	}
}