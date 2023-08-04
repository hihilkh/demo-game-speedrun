#include "ParticleSystem.h"
#include "GE/Core/GameObject.h"
#include "ParticleSystemLoader.h"
#include "CoreConfig.h"
#include "Module/ModuleSet.h"
#include "Internal/ParticleComponent.h"
#include "GE/Debug/Log.h"
#include "GE/Render/Image.h"

namespace GE::Particle
{
	namespace
	{
		const std::string particleInstanceName = "Particle";
	}

	ParticleSystem::ParticleSystem(GameObject& gameObject, const std::string& particleSystemFile) :
		Component(gameObject),
		coreConfig(),
		moduleSet()
	{
		ParticleSystemLoader::Load(particleSystemFile, coreConfig, moduleSet);
	}

	void ParticleSystem::Play() const
	{
		if (!coreConfig) {
			DEBUG_LOG_ERROR("coreConfigが見つけられない。ParticleSystem::Playできない。");
			return;
		}

		for (int i = 0; i < coreConfig->noOfParticle; ++i) {
			CreateParticleInstance();
		}
	}

	void ParticleSystem::CreateParticleInstance() const
	{
		if (coreConfig->imgFilePath == "") {
			DEBUG_LOG_ERROR("imgFilePathは空になる。ParticleSystemにImageが追加できない。");
			return;
		}

		GameObject& particle = gameObject.AddChild(particleInstanceName);

		auto& particleComponent = particle.AddComponent<Internal::ParticleComponent>(*coreConfig);

		auto& image = particle.AddComponent<Render::Image>(coreConfig->imgFilePath);
		image.SetRenderPriority(coreConfig->renderPriority);

		if (moduleSet) {
			moduleSet->ApplyModules(particleComponent);
		}
	}
}