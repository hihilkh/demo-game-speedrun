#include "GEHeader.h"
#include "GameEngine.h"

namespace GE
{
	void GameEngine::LoadScene(Scene&& scene)
	{
		GameEngine& ge = GetInstance();
		ge.RequestChangeScene(std::move(scene));
	}

	GameEngine::GameEngine() :
		isRunning(false)
	{
	}

	GameEngine& GameEngine::GetInstance()
	{
		static GameEngine ge;

		if (!ge.isRunning) {
			ge.Run();
		}

		return ge;
	}

	void GameEngine::Run()
	{
		if (isRunning) {
			return;
		}

		isRunning = true;

		// TODO : GameLoop

		CheckAndChangeScene();
	}

	void GameEngine::RequestChangeScene(Scene&& scene)
	{
		sceneToLoad.reset();

		if (loadedScenes.empty()) {
			ChangeScene(std::move(scene));
		} else {
			sceneToLoad = std::make_unique<Scene>(std::move(scene));
			CheckAndChangeScene();
		}
	}

	void GameEngine::CheckAndChangeScene()
	{
		if (!sceneToLoad.get()) {
			return;
		}

		ChangeScene(std::move(*sceneToLoad.release()));
	}

	void GameEngine::ChangeScene(Scene&& scene)
	{
		loadedScenes.clear();
		// TODO : アセットの破棄処理

		loadedScenes.push_back(std::move(scene));
	}
}

