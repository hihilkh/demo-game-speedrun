#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <tuple>

namespace GE::Particle
{
	struct CoreConfig;
	class ModuleSet;

	class ParticleSystemLoader
	{
	public:
		static void Load(const std::string& particleSystemFile, std::shared_ptr<CoreConfig>& outCoreConfig, std::shared_ptr<ModuleSet>& outModuleSet);

	private:
		static std::unordered_map<std::string, std::weak_ptr<CoreConfig>> loadedCoreConfigs;
		static std::unordered_map<std::string, std::weak_ptr<ModuleSet>> loadedModuleSets;

		static void LoadFromFile(const std::string& particleSystemFile, std::shared_ptr<CoreConfig>& outCoreConfig, std::shared_ptr<ModuleSet>& outModuleSet);
	};

}
