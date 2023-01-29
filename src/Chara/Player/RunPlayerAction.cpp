#include "RunPlayerAction.h"
#include "Utils/Log.h"
#include "PlayerConstant.h"

namespace Player
{
	RunPlayerAction::RunPlayerAction(Player::Object::WP player) :
		PlayerActionBase::PlayerActionBase(player),
		isRunning(false),
		prepareRunCounter(-1)
	{
	}

	RunPlayerAction::~RunPlayerAction()
	{
	}

	ML::Vec2 RunPlayerAction::PreMove()
	{
		auto playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return ML::Vec2();
		}

		XI::VGamePad input = GetInput();

		if (isRunning) {
			return UpdateRunning(playerSP, !input.ST.up);
		}

		if (input.ST.down) {
			return StartRunning(playerSP);
		}

		return TryWalk(input);
	}

	ML::Vec2 RunPlayerAction::StartRunning(Player::Object::SP playerSP)
	{
		isRunning = true;
		playerSP->state = PlayerState::Running;
		prepareRunCounter = 0;
		return ML::Vec2();
	}

	void RunPlayerAction::StopRunning(Player::Object::SP playerSP)
	{
		isRunning = false;
		playerSP->state = PlayerState::Idle;
	}

	ML::Vec2 RunPlayerAction::UpdateRunning(Player::Object::SP playerSP, bool hasInput)
	{
		++prepareRunCounter;

		switch (playerSP->state) {
			case PlayerState::Running:
				if (hasInput) {
					playerSP->currentMovementSpeed = CheckIsPrepareToRun() ? 0 : Constant::RunSpeed;
				}
				else {
					playerSP->state = PlayerState::Stopping;
				}
				break;
			case PlayerState::Stopping:
				Decelerate(playerSP);
				break;
		}

		return GetDirectionalVector(playerSP->transform->direction) * playerSP->currentMovementSpeed;
	}

	bool RunPlayerAction::CheckIsPrepareToRun() const
	{
		return prepareRunCounter < Constant::PrepareRunningPeriod;
	}

	void RunPlayerAction::Decelerate(Player::Object::SP playerSP)
	{
		playerSP->currentMovementSpeed -= Constant::Deceleration;

		if (playerSP->currentMovementSpeed <= 0) {
			playerSP->currentMovementSpeed = 0;
			StopRunning(playerSP);
		}
	}

	void RunPlayerAction::CollideWithMap()
	{
		if (isRunning) {
			isRunning = false;
		}
	}
}