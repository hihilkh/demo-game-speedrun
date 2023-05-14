#pragma once

#include "SceneConfig.h"
#include "Scene.h"
#include <memory>

namespace GE::SceneManagement
{
	class Scene;

	class SceneManager
	{
		friend class GameEngine;

	public:
		static Scene& GetActiveScene();

	private:
		static SceneConfig config;
		static std::unique_ptr<Scene> activeScene;

	private:
		static void SetConfig(SceneConfig&& config);
		static void LoadFirstScene();
		static void ChangeScene(const std::string& sceneName);
	};
}