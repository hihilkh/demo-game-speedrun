#pragma once

#include <memory>
#include <string>
#include <set>
#include <vector>
#include "GEConfig.h"

namespace GE
{
	struct MainProgramInitParams;
	struct Color;
	class GameObject;

	namespace Scene
	{
		struct SceneConfig;
		class Scene;
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
		static void SetBGColor(const Color& color) { GameEngine::config.bgColor = color; }

		static void SetSceneConfig(Scene::SceneConfig&& config);

		static int Start(const MainProgramInitParams& params);

		static void LoadScene(const std::string& sceneName);

		static void Destroy(GameObject& gameObject);

	private:
		static GEConfig config;

		static bool isStarted;
		static std::string sceneNameToLoad;
		static std::set<Internal::Destroyable*> toBeDestroySet_ActiveScene;
		static std::set<Internal::Destroyable*> toBeDestroySet_PersistentScene;

	private:
		GameEngine() = delete;

		static void Init(const MainProgramInitParams& params);

		static bool CheckIsGoingToChangeScene();

		static void RunGameLoop();

		static void UpdatePhase(const std::vector<Scene::Scene*>& scenes);
		static void RenderPhase(const std::vector<Scene::Scene*>& scenes);
		static void EndOfFramePhase(const std::vector<Scene::Scene*>& scenes);
		static void DestroyPhase();
		static void ChangeScenePhase();
	};
}