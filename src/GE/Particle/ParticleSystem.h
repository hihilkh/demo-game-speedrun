#pragma once

#include "GE/Core/Component.h"
#include <memory>
#include <vector>
#include "GE/Utils/GEConcept.h"
#include "CoreConfig.h"

namespace GE::Particle
{
	class Module;

	class ParticleSystem : public Component
	{
	public:
		ParticleSystem(GameObject& gameObject, CoreConfig& coreConfig);

		template<ParticleModuleType T>
		T& AddModule();

		void Play() const;

	private:
		CoreConfig coreConfig;
		std::vector<std::unique_ptr<Module>> modules;

	private:
		void CreateParticleInstance() const;
	};

#pragma region テンプレート定義

	template<ParticleModuleType T>
	T& ParticleSystem::AddModule()
	{
		Module& particleModule = *(modules.emplace_back(std::make_unique<T>()));
		return static_cast<T&>(particleModule);
	}

#pragma endregion
}