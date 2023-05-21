﻿#include "GameEngine.h"
#include "GE/MainProgram/MainProgram.h"
#include "GE/MainProgram/MainProgramInitParams.h"
#include "Time.h"
#include "GE/SceneManagement/SceneManager.h"
#include "GE/SceneManagement/Scene.h"
#include "GE/Render/RenderSystem.h"
#include "GE/Render/RenderSystemInitParams.h"
#include "Internal/Destroyable.h"
#include <cassert>

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;
	std::string GameEngine::sceneNameToLoad = "";
	std::set<Internal::Destroyable*> GameEngine::toBeDestroySet;

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

	void GameEngine::Destroy(Internal::Destroyable& toDestroy)
	{
		// ActiveSceneにいるではない場合、直接に破棄する
		if (!toDestroy.CheckIsInActiveScene()) {
			toDestroy.OnPreDestroy();
			toDestroy.OnDestroy();
			return;
		}

		auto result = toBeDestroySet.insert(&toDestroy);
		if (result.second) {	// insert成功 (重複しない場合)
			toDestroy.SetToBeDestroy();
		}
	}

	void GameEngine::DestroyPhase()
	{
		if (CheckIsGoingToChangeScene()) {
			// シーンの遷移とき、ActiveSceneの全てのDestroyableも破棄される
			// そういうわけで、下の処理をしなくてもいい
			toBeDestroySet.clear();
			return;
		} 

		std::vector<Internal::Destroyable*> finalDestroyObjects;

		for (auto destroyable : toBeDestroySet) {
			assert(destroyable && "なぜかdestroyableはnullptrになる");

			// GameObjectを破棄するとき、関連するcomponentsとchildrenも破棄する
			// 下記はすでに破棄したものを再び破棄しないような処理である
			if (destroyable->destroyState != Internal::Destroyable::State::Destroying) {
				finalDestroyObjects.push_back(destroyable);
				destroyable->OnPreDestroy();
			}
		}

		for (auto destroyable : finalDestroyObjects) {
			destroyable->OnDestroy();
		}

		toBeDestroySet.clear();
	}

	bool GameEngine::CheckIsGoingToChangeScene()
	{
		return !sceneNameToLoad.empty();
	}

	void GameEngine::CheckAndChangeScene()
	{
		if (!CheckIsGoingToChangeScene()) {
			return;
		}

		SceneManagement::SceneManager::ChangeScene(sceneNameToLoad);
		sceneNameToLoad = "";
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

		activeScene.OnEndOfFrame();
		DestroyPhase();

		CheckAndChangeScene();
	}
}

