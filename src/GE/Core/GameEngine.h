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
	class Scene;

	namespace SceneManagement
	{
		struct SceneConfig;
	}

	namespace Collision
	{
		class CollisionLayerMatrix;
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

		static void SetSceneConfig(SceneManagement::SceneConfig&& config);
		static void SetCollisionLayerMatrix(Collision::CollisionLayerMatrix&& matrix);

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

#pragma region ゲームループ
		static void RunGameLoop();

		static void TimeUpdatePhase();
		static void InputUpdatePhase();
		static void StartPhase(const std::vector<Scene*>& scenes);
		static void UpdatePhase(const std::vector<Scene*>& scenes);
		static void CollisionPhase();
		static void AnimationUpdatePhase();
		static void RenderPhase(const std::vector<Scene*>& scenes);
		static void DestroyPhase();
		static void ChangeScenePhase();

#pragma endregion
	};
}