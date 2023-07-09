#include "GE/GEHeader.h"
#include "PlayerPrepareToRunStateHandler.h"
#include "Character/Player/PlayerConfig.h"

namespace Player
{
	PlayerPrepareToRunStateHandler::PlayerPrepareToRunStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::PrepareToRun),
		startTime(0.0f)
	{
	}
	void PlayerPrepareToRunStateHandler::OnEnter()
	{
		startTime = Time::GetTime();
	}

	bool PlayerPrepareToRunStateHandler::CheckHasDoneState()
	{
		return Time::GetTime() - startTime >= prepareToRunPeriod;
	}
}

