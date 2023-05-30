#include "GameEngine.h"
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

namespace GE
{
	GEConfig GameEngine::config;
	bool GameEngine::isStarted = false;
	std::string GameEngine::sceneNameToLoad = "";
	std::set<Internal::Destroyable*> GameEngine::toBeDestroySet;

	void GameEngine::SetSceneConfig(Scene::SceneConfig&& config)
	{
		Scene::SceneManager::SetConfig(std::move(config));
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
		MainProgram::OtherInitParamsSet other = MainProgram::Prepare(params, config);
		Render::RenderSystem::Init(other.renderSystemInitParams, config);
		Time::Init(config.targetFps);
		Scene::SceneManager::LoadFirstScene();
	}

	void GameEngine::LoadScene(const std::string& sceneName)
	{
		// 実際のシーン遷移はChangeScenePhase()で行う
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

	void GameEngine::ChangeScenePhase()
	{
		if (!CheckIsGoingToChangeScene()) {
			return;
		}

		Scene::SceneManager::ChangeScene(sceneNameToLoad);
		sceneNameToLoad = "";
	}

	void GameEngine::RunGameLoop()
	{
		UpdatePhase();
		RenderPhase();
		EndOfFramePhase();
		DestroyPhase();
		ChangeScenePhase();
	}

	void GameEngine::UpdatePhase()
	{
		Scene::Scene& activeScene = Scene::SceneManager::GetActiveScene();

		Time::Update();

		Input::InputSystem::OnUpdate();

		activeScene.OnUpdate();
		activeScene.OnLateUpdate();
	}

	void GameEngine::RenderPhase()
	{
		Scene::Scene& activeScene = Scene::SceneManager::GetActiveScene();

		Render::RenderSystem::StartRender();
		activeScene.OnRender();
		Render::RenderSystem::FinishRender();
	}

	void GameEngine::EndOfFramePhase()
	{
		Scene::Scene& activeScene = Scene::SceneManager::GetActiveScene();
		activeScene.OnEndOfFrame();
	}
}

