#include "GE/GEHeader.h"
#include "GameSceneDirector.h"

#include "GE/Input/InputSystem.h"
#include "Scene/Builder/EndingScene.h"
#include "Scene/SceneTransition.h"
#include "Map/MapManager.h"
#include "Camera/CameraManagement.h"
#include "Character/Player/PlayerCameraController.h"

namespace GameScene
{
	GE::Event<> Director::onGameStarted;
	GE::Event<> Director::onGameEnded;

	GameState Director::gameState = GameState::NotInGame;
	bool Director::hasPerformedGoalZooming = false;

	Director::Director(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void Director::Awake()
	{
		gameState = GameState::Preparing;
		Map::MapManager::onMapLoaded.AddListener(&Director::SceneReadyHandler, *this);
	}

	void Director::PreDestroy()
	{
		Map::MapManager::onMapLoaded.RemoveListener(&Director::SceneReadyHandler, *this);
		gameState = GameState::NotInGame;
	}

	void Director::Update()
	{
		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			Scene::FadeOutAndChangeScene(Scene::endingSceneName);
		}
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
		// TODO
		DEBUG_LOG("CountdownToStart");
		StartGame();
	}

	void Director::StartGame()
	{
		// TODO
		gameState = GameState::Started;
	}
}