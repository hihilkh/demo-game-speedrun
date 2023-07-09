#pragma once

#include "PlayerStateHandler.h"

namespace Player
{
	class PlayerPrepareToRunStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerPrepareToRunStateHandler(PlayerModel& model);

		void OnEnter() override;
		bool CheckHasDoneState() override;

	private:
		float startTime;
	};
}