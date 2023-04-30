#pragma once

#include <vector>
#include <memory>
#include "GEConfig.h"

#include <windows.h>

namespace GE
{
	class Scene;

	class GameEngine
	{
	public:
		static void SetConfig(const GEConfig& config) { GameEngine::config = config; }
		static const GEConfig& GetConfig() { return config; }

		static int Start(HINSTANCE hInstance, int nCmdShow, Scene&& scene);

		// TODO : マルチシーンを支援する
		static void LoadScene(Scene&& scene);

	private:
		static GEConfig config;
		static bool isStarted;

		static std::vector<Scene> loadedScenes;
		static std::unique_ptr<Scene> sceneToLoad;

	private:
		GameEngine() = delete;

		static void Init(Scene&& scene);

		static void RequestChangeScene(Scene&& scene);
		static void CheckAndChangeScene();
		static void ChangeScene(Scene&& scene);
		static void RunGameLoop();

#pragma region ゲームウィンドウ

		static HWND CreateGameWindow(HINSTANCE hInstance);

#pragma endregion

	};
}