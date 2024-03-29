﻿#include "GameEngine.h"
#include "GE/MainProgram/MainProgram.h"
#include "GE/MainProgram/MainProgramInitParams.h"
#include "Time.h"
#include "GE/Scene/SceneManager.h"
#include "GE/Scene/Scene.h"
#include "GE/Render/RenderSystem.h"
#include "GE/Render/RenderSystemInitParams.h"
#include "GE/Input/InputSystem.h"
#include "Internal/Destroyable.h"
#include <cassert>
#include <algorithm>
#include "GE/Profiling/Profiler.h"
#include "GE/Collision/CollisionSystem.h"
#include "GE/Animation/AnimationSystem.h"
#include <ctime>
#include <cstdlib>

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;
	std::string GameEngine::sceneNameToLoad = "";
	std::set<Internal::Destroyable*> GameEngine::toBeDestroySet_ActiveScene;
	std::set<Internal::Destroyable*> GameEngine::toBeDestroySet_PersistentScene;

	void GameEngine::SetSceneConfig(SceneManagement::SceneConfig&& config)
	{
		SceneManagement::SceneManager::SetConfig(std::move(config));
	}

	void GameEngine::SetCollisionLayerMatrix(Collision::CollisionLayerMatrix&& matrix)
	{
		Collision::CollisionSystem::SetCollisionLayerMatrix(std::move(matrix));
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
		std::srand((unsigned)time(nullptr));
		MainProgram::OtherInitParamsSet other = MainProgram::Prepare(params, config);
		Render::RenderSystem::Init(other.renderSystemInitParams, config);
		Time::Init(config.targetFps);
		DEBUG_START_PROFILING();
		SceneManagement::SceneManager::LoadFirstScene();
	}

	void GameEngine::LoadScene(const std::string& sceneName)
	{
		// 実際のシーン遷移はChangeScenePhase()で行う
		sceneNameToLoad = sceneName;
	}

	void GameEngine::Destroy(GameObject& gameObject)
	{
		const Scene& belongingScene = gameObject.GetBelongingScene();
		const std::vector<Scene*> loadedScenes = SceneManagement::SceneManager::GetLoadedScenes();

		Internal::Destroyable& toDestroy = static_cast<Internal::Destroyable&>(gameObject);
		// ActiveSceneにいるではない場合、直接に破棄する
		if (std::none_of(
				loadedScenes.begin(), loadedScenes.end(), 
				[&belongingScene](Scene* scene) { return scene == &belongingScene; }))
		{
			toDestroy.OnPreDestroy();
			toDestroy.OnDestroy();
			return;
		}

		auto result = belongingScene == SceneManagement::SceneManager::GetActiveScene() ?
			toBeDestroySet_ActiveScene.insert(&toDestroy) :
			toBeDestroySet_PersistentScene.insert(&toDestroy);
		if (result.second) {	// insert成功 (重複しない場合)
			toDestroy.SetToBeDestroy();
		}
	}

	bool GameEngine::CheckIsGoingToChangeScene()
	{
		return !sceneNameToLoad.empty();
	}

#pragma region ゲームループ

	void GameEngine::RunGameLoop()
	{
		std::vector<Scene*> loadedScenes = SceneManagement::SceneManager::GetLoadedScenes();

		TimeUpdatePhase();
		InputUpdatePhase();
		StartPhase(loadedScenes);
		UpdatePhase(loadedScenes);
		CollisionPhase();
		AnimationUpdatePhase();
		RenderPhase(loadedScenes);
		DestroyPhase();
		ChangeScenePhase();
	}

	void GameEngine::TimeUpdatePhase()
	{
		Time::OnUpdate();
	}

	void GameEngine::InputUpdatePhase()
	{
		Input::InputSystem::OnUpdate();
	}

	void GameEngine::StartPhase(const std::vector<Scene*>& scenes)
	{
		for (auto scene : scenes) {
			scene->OnStartUnstarted();
		}
	}

	void GameEngine::UpdatePhase(const std::vector<Scene*>& scenes)
	{
		for (auto scene : scenes) {
			scene->OnUpdate();
		}

		for (auto scene : scenes) {
			scene->OnLateUpdate();
		}
	}

	void GameEngine::CollisionPhase()
	{
		Collision::CollisionSystem::OnStartCollision();
	}

	void GameEngine::AnimationUpdatePhase()
	{
		Animation::AnimationSystem::OnAnimationUpdate();
	}

	void GameEngine::RenderPhase(const std::vector<Scene*>& scenes)
	{
		Render::RenderSystem::OnStartRender();
		Scene::OnRender(scenes);
		Render::RenderSystem::OnFinishRender();
	}

	void GameEngine::DestroyPhase()
	{
		if (CheckIsGoingToChangeScene()) {
			// シーンの遷移とき、ActiveSceneの全てのDestroyableも破棄される
			// そういうわけで、toBeDestroySet_ActiveSceneの処理をしなくてもいい
			toBeDestroySet_ActiveScene.clear();
		}

		std::vector<Internal::Destroyable*> finalDestroyObjects;

		std::set<Internal::Destroyable*>* toBeDestroySets[] = {
			&toBeDestroySet_ActiveScene,
			&toBeDestroySet_PersistentScene };

		for (auto toBeDestroySet : toBeDestroySets) {
			for (auto destroyable : *toBeDestroySet) {
				assert(destroyable && "なぜかdestroyableはnullptrになる");

				// GameObjectを破棄するとき、関連するcomponentsとchildrenも破棄する
				// 下記はすでに破棄したものを再び破棄しないような処理である
				if (destroyable->destroyState != Internal::Destroyable::State::Destroying) {
					finalDestroyObjects.push_back(destroyable);
					destroyable->OnPreDestroy();
				}
			}
		}

		for (auto destroyable : finalDestroyObjects) {
			destroyable->OnDestroy();
		}

		for (auto toBeDestroySet : toBeDestroySets) {
			toBeDestroySet->clear();
		}
	}

	void GameEngine::ChangeScenePhase()
	{
		if (!CheckIsGoingToChangeScene()) {
			return;
		}

		SceneManagement::SceneManager::ChangeScene(sceneNameToLoad);
		sceneNameToLoad = "";
	}

#pragma endregion

}

