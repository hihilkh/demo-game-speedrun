#pragma once

#include "PlayerStateHandler.h"

namespace Player
{
	class PlayerStopRunningStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerStopRunningStateHandler(PlayerModel& model);

		void OnEnter() override;
		void OnUpdate() override;
		void OnExit() override;

		bool CheckHasDoneState() override;

	private:
		float currentSpeed;
	};
}