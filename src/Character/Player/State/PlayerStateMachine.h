#pragma once

#include <memory>
#include <vector>

#include "PlayerState.h"
#include "PlayerStateRequest.h"

namespace Player
{
	class PlayerModel;
	class PlayerStateHandler;

	class PlayerStateMachine
	{
	public:
		explicit PlayerStateMachine(PlayerModel& model);
		~PlayerStateMachine();

		PlayerState GetState() const;

		void AddStateRequest(PlayerStateRequest request);

		void Update();

	private:
		PlayerModel& model;
		std::unique_ptr<PlayerStateHandler> stateHandler;
		std::vector<PlayerStateRequest> stateRequests;

	private:
		void DetermineState();
		void DetermineState_Walk();
		void DetermineState_Run();
		void DetermineState_Fallback();

		void ChangeState(PlayerState state);
		std::unique_ptr<PlayerStateHandler> CreateStateHandler(PlayerState state) const;
	};
}