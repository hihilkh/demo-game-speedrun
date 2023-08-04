#pragma once

#include "../PlayerState.h"

namespace Player
{
	class PlayerModel;

	class PlayerStateHandler
	{
	public:
		virtual ~PlayerStateHandler() = default;

		virtual void OnEnter() {}
		virtual void OnUpdate() {}
		virtual void OnExit() {}

		virtual bool CheckHasDoneState() { return false; }

		PlayerState GetState() const { return state; }

	protected:
		PlayerModel& model;

	protected:
		explicit PlayerStateHandler(PlayerModel& model, PlayerState state) : 
			model(model),
			state(state) 
		{
		}

	private:
		PlayerState state;
	};
}