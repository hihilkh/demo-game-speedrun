#include "RunPlayerAction.h"
#include "Debug/Log.h"
#include "PlayerConstant.h"

namespace Player
{
	RunPlayerAction::RunPlayerAction(Player::Object::WP player) :
		PlayerActionBase::PlayerActionBase(player),
		isRunning(false),
		currentRunningSpeed(0),
		prepareToRunCounter(-1)
	{
	}

	RunPlayerAction::~RunPlayerAction()
	{
	}

	ML::Vec2 RunPlayerAction::PreMove()
	{
		auto playerSP = player.lock();
		if (!playerSP) {
			DEBUG_LOG_WARNING("プレイヤーの参照が取れない");
			return ML::Vec2();
		}

		XI::VGamePad input = GetInput();

		if (isRunning) {
			return UpdateRunning(playerSP, !input.B2.up);
		}

		if (input.B2.down) {
			return PrepareToRun(playerSP);
		}

		return TryWalk(input);
	}

	ML::Vec2 RunPlayerAction::PrepareToRun(Player::Object::SP playerSP)
	{
		//Print("PrepareToRun");
		isRunning = true;
		playerSP->state = PlayerState::PrepareToRun;
		prepareToRunCounter = 0;
		return ML::Vec2();
	}

	void RunPlayerAction::StopRunning(Player::Object::SP playerSP)
	{
		DEBUG_LOG("StopRunning");
		isRunning = false;
		currentRunningSpeed = 0;
		playerSP->state = PlayerState::Idle;
	}

	ML::Vec2 RunPlayerAction::UpdateRunning(Player::Object::SP playerSP, bool hasInput)
	{
		++prepareToRunCounter;

		switch (playerSP->state) {
			case PlayerState::PrepareToRun:
				SetAndApplyRunningSpeed(playerSP, 0);
				if (hasInput) {
					if (CheckIsReadyToRun()) {
						playerSP->state = PlayerState::Running;
						SetAndApplyRunningSpeed(playerSP, Constant::RunSpeed);
					}
				}
				else {
					playerSP->state = PlayerState::Stopping;
				}
				break;
			case PlayerState::Running:
				SetAndApplyRunningSpeed(playerSP, Constant::RunSpeed);
				if (!hasInput) {
					playerSP->state = PlayerState::Stopping;
				}
				break;
			case PlayerState::Stopping:
				Decelerate(playerSP);
				break;
		}

		return GetDirectionalVector(playerSP->transform->direction) * playerSP->currentMovementSpeed;
	}

	bool RunPlayerAction::CheckIsReadyToRun() const
	{
		return prepareToRunCounter >= Constant::PrepareRunningPeriod;
	}

	void RunPlayerAction::SetAndApplyRunningSpeed(Player::Object::SP playerSP, float speed)
	{
		currentRunningSpeed = speed;
		playerSP->currentMovementSpeed = speed;
	}

	void RunPlayerAction::Decelerate(Player::Object::SP playerSP)
	{
		float speedToDecelerate = min(currentRunningSpeed, Constant::Deceleration);
		SetAndApplyRunningSpeed(playerSP, currentRunningSpeed - speedToDecelerate);

		if (currentRunningSpeed <= 0) {
			StopRunning(playerSP);
		}
	}

	void RunPlayerAction::CollidedWithMap(const vector<Direction>& collidedDirections)
	{
		if (!isRunning) {
			return;
		}

		auto playerSP = player.lock();
		if (!playerSP) {
			DEBUG_LOG_WARNING("プレイヤーの参照が取れない");
			return;
		}

		for (Direction direction : collidedDirections) {
			// 反対方向
			if (CompareDirection(direction, playerSP->transform->direction) == -1) {
				if (playerSP->state != PlayerState::PrepareToRun) {
					isRunning = false;
					return;
				}
			}
		}

	}
}