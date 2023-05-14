#include "GameEngine.h"
#include "MainProgram/MainProgram.h"
#include "MainProgram/MainProgramInitParams.h"
#include "Time.h"
#include "SceneManagement/SceneManager.h"
#include "SceneManagement/Scene.h"
#include "Render/RenderSystem.h"
#include "Render/RenderSystemInitParams.h"

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;
	std::string GameEngine::sceneNameToLoad = "";

	void GameEngine::SetSceneConfig(SceneManagement::SceneConfig&& config)
	{
		SceneManagement::SceneManager::SetConfig(std::move(config));
	}

	// 参考：https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170
	int GameEngine::Start(const MainProgramInitParams& params)
	{
		if (isStarted) {
			return 0;
		}

		isStarted = true;

		Init(params);
		return MainProgram::Start(GameEngine::RunGameLoop);		
	}

	void GameEngine::Init(const MainProgramInitParams& params)
	{
		auto renderSystemInitParams = MainProgram::Prepare(params, config);
		Render::RenderSystem::Init(renderSystemInitParams, config);
		Time::Init(config.targetFps);
		SceneManagement::SceneManager::LoadFirstScene();
	}

	void GameEngine::LoadScene(const std::string& sceneName)
	{
		// 実際のシーン遷移はCheckAndChangeScene()で行う
		sceneNameToLoad = sceneName;
	}

	void GameEngine::CheckAndChangeScene()
	{
		if (sceneNameToLoad.empty()) {
			return;
		}

		SceneManagement::SceneManager::ChangeScene(sceneNameToLoad);
	}

	void GameEngine::RunGameLoop()
	{
		Time::Update();

		SceneManagement::Scene& activeScene = SceneManagement::SceneManager::GetActiveScene();
		activeScene.OnUpdate();
		activeScene.OnLateUpdate();

		Render::RenderSystem::StartRender();
		activeScene.OnRender();
		Render::RenderSystem::FinishRender();

		CheckAndChangeScene();
	}
}

