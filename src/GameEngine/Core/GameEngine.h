#pragma once

#include <memory>
#include <string>
#include "GEConfig.h"

#include <windows.h>

namespace GE
{
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

		static int Start(HINSTANCE hInstance, int nCmdShow);

		static void LoadScene(const std::string& sceneName);

	private:
		static GEConfig config;
		static bool isStarted;
		static std::string sceneNameToLoad;

	private:
		GameEngine() = delete;

		static void InitEngine();

		static void CheckAndChangeScene();
		static void RunGameLoop();

#pragma region Windows プラットフォーム

		static int StartWithWindows(HINSTANCE hInstance, int nCmdShow);
		static HWND CreateGameWindow(HINSTANCE hInstance);

#pragma endregion

	};
}