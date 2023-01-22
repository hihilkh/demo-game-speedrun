#include "Reference.h"

namespace Game
{
	weak_ptr<Map::Object> Reference::map;
	weak_ptr<Camera::Object> Reference::gameCamera;
	weak_ptr<Player::Object> Reference::player;
	weak_ptr<Status> Reference::gameStatus;
}