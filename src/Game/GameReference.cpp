﻿#include "GameReference.h"

// TODO : GameReferenceが必要かどうかを検討
namespace Game
{
	weak_ptr<Map::Object> GameReference::map;
	weak_ptr<Camera::Object> GameReference::gameCamera;
	weak_ptr<Player::Object> GameReference::player;
	weak_ptr<GameStatus> GameReference::gameStatus;
}