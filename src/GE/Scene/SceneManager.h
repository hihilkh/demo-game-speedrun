#pragma once

#include "SceneConfig.h"
#include "Scene.h"
#include <memory>
#include <vector>

namespace GE::Scene
{
	class Scene;

	class SceneManager
	{
		friend class GameEngine;

	public:
		static Scene& GetActiveScene() { return *activeScene; }
		static Scene& GetPersistentScene() { return *persistentScene; }
		static std::vector<Scene*> GetLoadedScenes();

	private:
		static SceneConfig config;
		static std::unique_ptr<Scene> activeScene;
		static std::unique_ptr<Scene> persistentScene;

	private:
		static void SetConfig(SceneConfig&& config) { SceneManager::config = std::move(config); }
		static void LoadFirstScene();
		static void ChangeScene(const std::string& sceneName);
	};
}