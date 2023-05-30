#pragma once

#include <memory>
#include <string>
#include <set>
#include "GEConfig.h"

namespace GE
{
	struct MainProgramInitParams;
	namespace Scene
	{
		struct SceneConfig;
	}

	namespace Internal
	{
		class Destroyable;
	}

	class GameEngine
	{
	public:
		static void SetConfig(const GEConfig& config) { GameEngine::config = config; }
		static const GEConfig& GetConfig() { return config; }

		static void SetSceneConfig(Scene::SceneConfig&& config);

		static int Start(const MainProgramInitParams& params);

		static void LoadScene(const std::string& sceneName);

		static void Destroy(Internal::Destroyable& toDestroy);

	private:
		static GEConfig config;

		static bool isStarted;
		static std::string sceneNameToLoad;
		static std::set<Internal::Destroyable*> toBeDestroySet;

	private:
		GameEngine() = delete;

		static void Init(const MainProgramInitParams& params);

		static bool CheckIsGoingToChangeScene();

		static void RunGameLoop();

		static void UpdatePhase();
		static void RenderPhase();
		static void EndOfFramePhase();
		static void DestroyPhase();
		static void ChangeScenePhase();
	};
}