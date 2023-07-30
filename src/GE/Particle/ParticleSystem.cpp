#include "ParticleSystem.h"
#include <string>
#include "GE/Core/GameObject.h"
#include "Module/Module.h"
#include "Internal/ParticleComponent.h"
#include "GE/Debug/Log.h"
#include "GE/Render/Image.h"

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

	void ParticleSystem::Play() const
	{
		for (int i = 0; i < coreConfig.noOfParticle; ++i) {
			CreateParticleInstance();
		}
	}

	void ParticleSystem::CreateParticleInstance() const
	{
		if (coreConfig.imgFilePath == "") {
			DEBUG_LOG_ERROR("imgFilePathは空になる。ParticleSystemにImageが追加できない。");
			return;
		}

		GameObject& particle = gameObject.AddChild(particleInstanceName);

		auto& particleComponent = particle.AddComponent<Internal::ParticleComponent>(coreConfig);

		auto& image = particle.AddComponent<Render::Image>(coreConfig.imgFilePath);
		image.SetRenderPriority(coreConfig.renderPriority);

		for (auto& particleModule : modules) {
			particleModule->ApplyModule(particleComponent);
		}
	}
}