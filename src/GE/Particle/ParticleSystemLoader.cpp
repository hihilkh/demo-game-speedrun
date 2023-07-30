#include "ParticleSystemLoader.h"
#include "GE/Utils/Json.h"
#include "CoreConfig.h"
#include "Module/ModuleSet.h"
#include "GE/Debug/Log.h"
#include "Module/RectEmissionModule.h"
#include "Module/VelocityModule.h"
#include "Module/ColorOverLifetimeModule.h"

namespace GE::Particle
{
	namespace
	{
		const std::string coreNode = "core";
		const std::string imageNode = "img";
		const std::string renderPriorityNode = "render_priority";
		const std::string noOfParticleNode = "no_of_particle";
		const std::string lifeNode = "life";

		const std::string modulesNode = "modules";
		const std::string moduleNameNode = "name";
		const std::string moduleDetailNode = "detail";

		const std::string rectEmissionNameNode = "rectEmission";
		const std::string velocityNameNode = "velocity";
		const std::string colorOverLifetimeNameNode = "colorOverLifetime";
	}

	namespace
	{
		template<typename T>
		std::shared_ptr<T> GetCache(const std::unordered_map<std::string, std::weak_ptr<T>>& cacheMap, const std::string& particleSystemFile)
		{
			if (auto cache = cacheMap.find(particleSystemFile); cache != cacheMap.end()) {
				if (!cache->second.expired()) {
					return cache->second.lock();
				}
			}

			return nullptr;
		}

		std::shared_ptr<CoreConfig> ConvertToCoreConfig(const GE::Json::Value& json)
		{
			std::shared_ptr<CoreConfig> coreConfig = std::make_shared<CoreConfig>();
			coreConfig->imgFilePath = json[imageNode].asString();
			coreConfig->renderPriority = json[renderPriorityNode].asInt();
			coreConfig->noOfParticle = json[noOfParticleNode].asInt();
			coreConfig->life = json[lifeNode].asFloat();

			return coreConfig;
		}

		std::unique_ptr<Module> ConvertToModule(const std::string& name, const GE::Json::Value& json)
		{
			std::unique_ptr<Module> particleModule = nullptr;

			if (name == rectEmissionNameNode) {
				particleModule = std::make_unique<RectEmissionModule>(json);
			} else if (name == velocityNameNode) {
				particleModule = std::make_unique<VelocityModule>(json);
			} else if (name == colorOverLifetimeNameNode) {
				particleModule = std::make_unique<ColorOverLifetimeModule>(json);
			}

			if (!particleModule) {
				DEBUG_LOG_ERROR("ParticleModuleの生成は失敗した。Module name：" << name);
			}

			return particleModule;
		}
	}
	
	std::unordered_map<std::string, std::weak_ptr<CoreConfig>> ParticleSystemLoader::loadedCoreConfigs;
	std::unordered_map<std::string, std::weak_ptr<ModuleSet>> ParticleSystemLoader::loadedModuleSets;

	void ParticleSystemLoader::Load(const std::string& particleSystemFile, std::shared_ptr<CoreConfig>& outCoreConfig, std::shared_ptr<ModuleSet>& outModuleSet)
	{
		outCoreConfig = GetCache(loadedCoreConfigs, particleSystemFile);
		outModuleSet = GetCache(loadedModuleSets, particleSystemFile);

		if (!outCoreConfig || !outModuleSet) {
			LoadFromFile(particleSystemFile, outCoreConfig, outModuleSet);
		}
	}

	void ParticleSystemLoader::LoadFromFile(const std::string& particleSystemFile, std::shared_ptr<CoreConfig>& outCoreConfig, std::shared_ptr<ModuleSet>& outModuleSet)
	{
		auto json = GE::Json::LoadJson(particleSystemFile);

		const auto& coreJson = json[coreNode];
		outCoreConfig = ConvertToCoreConfig(coreJson);
		loadedCoreConfigs[particleSystemFile] = outCoreConfig;

		const auto& modulesJson = json[modulesNode];
		outModuleSet = std::make_shared<ModuleSet>();

		for (const auto& moduleJson : modulesJson) {
			std::string name = moduleJson[moduleNameNode].asString();
			const auto& moduleDetailJson = moduleJson[moduleDetailNode];
			std::unique_ptr<Module> particleModule = ConvertToModule(name, moduleDetailJson);
			if (particleModule) {
				outModuleSet->AddModule(std::move(particleModule));
			}
		}

		loadedModuleSets[particleSystemFile] = outModuleSet;
	}
}