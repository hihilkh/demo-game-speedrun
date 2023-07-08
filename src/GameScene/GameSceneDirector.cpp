#include "GE/GEHeader.h"
#include "GameSceneDirector.h"

#include "GE/Input/InputSystem.h"
#include "Scene/Builder/EndingScene.h"
#include "Scene/SceneTransition.h"
#include "Map/MapManager.h"
#include "Camera/CameraManagement.h"
#include "Character/Player/PlayerCameraController.h"
#include "GameTimerController.h"

#include "GameProgress.h"

#include "Prefab/UI/CountDownUIPrefab.h"
#include "UI/CountDownUI.h"

namespace GameScene
{
	namespace
	{
		const int countDownSecond = 3;
		const std::string finishCountDownText = "スタート";
	}

	GE::Event<> Director::onGameStarted;
	GE::Event<> Director::onGameCleared;

	GameState Director::gameState = GameState::NotInGame;
	bool Director::hasPerformedGoalZooming = false;

	Director::Director(GameObject& gameObject, GameTimerController& timerController) :
		Component(gameObject),
		timerController(timerController)
	{
	}

	void Director::Awake()
	{
		gameState = GameState::Preparing;
		GameProgress::CreateNewGameProgress();
		Map::MapManager::onMapLoaded.AddListener(&Director::SceneReadyHandler, *this);
	}

	void Director::PreDestroy()
	{
		Map::MapManager::onMapLoaded.RemoveListener(&Director::SceneReadyHandler, *this);
		gameState = GameState::NotInGame;
	}

	void Director::Update()
	{
#ifdef _DEBUG
		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			GoToEndingScene();
		}
#endif
	}

	void Director::SceneReadyHandler(const Map::MapManager& mapManager)
	{
		Vector2 goalPos = mapManager.GetGoalPos();
		Scene::FadeIn([this, goalPos] { this->StartOpening(goalPos); });
	}

	void Director::StartOpening(const Vector2& goalPos)
	{
		if (!hasPerformedGoalZooming) {
			hasPerformedGoalZooming = true;

			GE::Camera2D* mainCamera = Camera::GetMainCamera();
			if (mainCamera != nullptr) {
				auto playerCameraController = mainCamera->gameObject.GetComponent<Player::PlayerCameraController>();

				if (playerCameraController != nullptr) {
					playerCameraController->PerformZoom(goalPos, [this] { this->CountdownToStart(); });
				}
			}
		} else {
			CountdownToStart();
		}
	}

	void Director::CountdownToStart()
	{
		auto& countDownUI = GE::Instantiate(Prefab::UI::CountDownUIPrefab());
		countDownUI.StartCountDown(
			countDownSecond, 
			finishCountDownText, 
			[this] { this->StartGame(); });
	}

	void Director::StartGame()
	{
		gameState = GameState::Started;
		timerController.StartTimer();
		onGameStarted.Invoke();
	}

	void Director::GameClear()
	{
		gameState = GameState::Ended;
		timerController.PauseTimer();
		GameProgress::GetCurrentGameProgress().SetGameClearTime(timerController.GetCountedTime());
		onGameCleared.Invoke();
		GoToEndingScene();
	}

	void Director::GoToEndingScene() const
	{
		Scene::FadeOutAndChangeScene(Scene::endingSceneName);
	}
}