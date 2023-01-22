#pragma once

#include "myLib.h"

#pragma region 前方宣言

namespace Map { class Object; }
namespace Game::Camera { class Object; }
namespace Player { class Object; }
namespace Game 
{ 
	class Object;
	class GameStatus;
}

#pragma endregion

namespace Game
{
	class GameReference
	{
		friend Game::Object;

	private:
		static weak_ptr<Map::Object> map;
		static weak_ptr<Camera::Object> gameCamera;
		static weak_ptr<Player::Object> player;
		static weak_ptr<GameStatus> gameStatus;

	public:
		static shared_ptr<Map::Object> GetMap() { return map.lock(); }
		static shared_ptr<Camera::Object> GetGameCamera() { return gameCamera.lock(); }
		static shared_ptr<Player::Object> GetPlayer() { return player.lock(); }
		static shared_ptr<GameStatus> GetGameStatus() { return gameStatus.lock(); }
	};
}