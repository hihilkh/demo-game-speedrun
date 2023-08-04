#pragma once

#include "GE/Utils/TypeDef.h"

namespace Player
{
	class PlayerModel;
}

namespace Prefab::Player
{
	class PlayerPrefab
	{
	public:
		::Player::PlayerModel& operator()(GameObject& baseGameObject) const;
	};
}