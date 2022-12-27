#pragma once

#include "Task_Game.h"
#include "Task_Map.h"
#include "Task_GameCamera.h"
#include "Task_Player.h"
#include "GameStatus.h"

namespace Game
{
	class GameReference
	{
		friend Game::Object;

	private:
		static Map::Object::WP map;
		static GameCamera::Object::WP gameCamera;
		static Player::Object::WP player;
		static GameStatus::WP gameStatus;

	public:
		static Map::Object::SP GetMap() { return map.lock(); }
		static GameCamera::Object::SP GetGameCamera() { return gameCamera.lock(); }
		static Player::Object::SP GetPlayer() { return player.lock(); }
		static GameStatus::SP GetGameStatus() { return gameStatus.lock(); }
	};
}