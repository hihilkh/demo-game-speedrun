#pragma once

#include <memory>
#include <string>
#include "GEConfig.h"

namespace GE
{
	struct MainProgramInitParams;
	namespace SceneManagement
	{
		struct SceneConfig;
	}


	class GameEngine
	{
	public:
		static void SetConfig(const GEConfig& config) { GameEngine::config = config; }
		static const GEConfig& GetConfig() { return config; }

		static void SetSceneConfig(SceneManagement::SceneConfig&& config);

		static int Start(const MainProgramInitParams& params);

		static void LoadScene(const std::string& sceneName);

	private:
		static GEConfig config;

		static bool isStarted;
		static std::string sceneNameToLoad;

	private:
		GameEngine() = delete;

		static void Init(const MainProgramInitParams& params);

		static void CheckAndChangeScene();
		static void RunGameLoop();
	};
}