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
	class Director : public Component
	{
	public:
		static GE::Event<> onGameStarted;
		static GE::Event<> onGameEnded;

	public:
		explicit Director(GameObject& gameObject);
		static GameState GetGameState() { return gameState; }

	protected:
		void Awake() override;
		void PreDestroy() override;
		void Update() override;

	private:
		static GameState gameState;
		static bool hasPerformedGoalZooming;

	private:
		void SceneReadyHandler(const Map::MapManager& mapManager);
		void StartOpening(const Vector2& goalPos);
		void CountdownToStart();
		void StartGame();
	};
}