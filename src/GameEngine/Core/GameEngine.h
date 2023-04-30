#pragma once

#include <vector>
#include "Scene.h"
#include <memory>

namespace GE
{
	class GameEngine
	{
	public:
		// TODO : マルチシーンを支援する
		static void LoadScene(Scene&& scene);

	private:
		std::vector<Scene> loadedScenes;
		std::unique_ptr<Scene> sceneToLoad;

		bool isRunning;

	private:
		GameEngine();
		GameEngine(const GameEngine&) = delete;
		void operator=(const GameEngine&) = delete;

		static GameEngine& GetInstance();

		void Run();
		void RequestChangeScene(Scene&& scene);
		void CheckAndChangeScene();
		void ChangeScene(Scene&& scene);

	};
}