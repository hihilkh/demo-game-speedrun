#include "GameReference.h"

namespace Game
{
	Map::Object::WP GameReference::map;
	GameCamera::Object::WP GameReference::gameCamera;
	Player::Object::WP GameReference::player;
	GameStatus::WP GameReference::gameStatus;
}