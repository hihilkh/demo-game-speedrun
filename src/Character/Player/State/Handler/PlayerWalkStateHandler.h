#pragma once

#include "PlayerStateHandler.h"

namespace Player
{
	class PlayerWalkStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerWalkStateHandler(PlayerModel& model);

		void OnUpdate() override;
	};
}