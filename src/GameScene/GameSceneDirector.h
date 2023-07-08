#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Event.h"
#include "GameState.h"

namespace Map
{
	class MapManager;
}

namespace GameScene
{
	class GameTimerController;

	class Director : public Component
	{
	public:
		static GE::Event<> onGameStarted;
		static GE::Event<> onGameCleared;

	public:
		Director(GameObject& gameObject, GameTimerController& timerController);
		static GameState GetGameState() { return gameState; }

	protected:
		void Awake() override;
		void PreDestroy() override;
		void Update() override;

	private:
		GameTimerController& timerController;
		static GameState gameState;
		static bool hasPerformedGoalZooming;

	private:
		void SceneReadyHandler(const Map::MapManager& mapManager);
		void StartOpening(const Vector2& goalPos);
		void CountdownToStart();
		void StartGame();
		void GameClear();
		void GoToEndingScene() const;
	};
}