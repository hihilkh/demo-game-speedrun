#include "GameReference.h"

namespace Game
{
	weak_ptr<Map::Object> GameReference::map;
	weak_ptr<GameCamera::Object> GameReference::gameCamera;
	weak_ptr<Player::Object> GameReference::player;
	weak_ptr<GameStatus> GameReference::gameStatus;
}