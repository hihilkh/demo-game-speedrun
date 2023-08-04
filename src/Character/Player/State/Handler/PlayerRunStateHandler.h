#pragma once

#include "PlayerStateHandler.h"

namespace Player
{
	class PlayerRunStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerRunStateHandler(PlayerModel& model);

		void OnUpdate() override;
	};
}