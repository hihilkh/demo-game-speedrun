#pragma once

#include "PlayerStateHandler.h"

namespace Player
{
	class PlayerFallbackStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerFallbackStateHandler(PlayerModel& model);
	};
}