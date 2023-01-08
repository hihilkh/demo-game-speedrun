#include "RunPlayerAction.h"
#include "Utils/Log.h"
#include "PlayerConstant.h"

namespace Player
{
	RunPlayerAction::RunPlayerAction(Player::Object::SP player, XI::GamePad::SP controller) :
		PlayerActionBase::PlayerActionBase(player, controller),
		isRunning(false),
		prepareRunCounter(-1)
	{
	}

	RunPlayerAction::~RunPlayerAction()
	{
	}

	void RunPlayerAction::UpDate()
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return;
		}

		XI::VGamePad input = controller->GetState();

		if (isRunning) {
			UpdateRunning(playerSP, !input.ST.up);
			return;
		}

		if (input.ST.down) {
			StartRunning(playerSP);
			return;
		}

		Move(input);
	}

	void RunPlayerAction::StartRunning(Player::Object::SP playerSP)
	{
		isRunning = true;
		playerSP->state = PlayerState::Running;
		prepareRunCounter = 0;
	}

	void RunPlayerAction::StopRunning(Player::Object::SP playerSP)
	{
		isRunning = false;
		playerSP->state = PlayerState::Idle;
	}

	void RunPlayerAction::UpdateRunning(Player::Object::SP playerSP, bool hasInput)
	{
		++prepareRunCounter;

		switch (playerSP->state) {
			case PlayerState::Running:
				if (hasInput) {
					playerSP->currentMovementSpeed = CheckIsPrepareToRun() ? 0 : PlayerConstant::RunSpeed;
				}
				else {
					playerSP->state = PlayerState::Stopping;
				}
				break;
			case PlayerState::Stopping:
				Decelerate(playerSP);
				break;
		}

		Run(playerSP);
	}

	bool RunPlayerAction::CheckIsPrepareToRun() const
	{
		return prepareRunCounter < PlayerConstant::PrepareRunningPeriod;
	}

	void RunPlayerAction::Decelerate(Player::Object::SP playerSP)
	{
		playerSP->currentMovementSpeed -= PlayerConstant::Deceleration;

		if (playerSP->currentMovementSpeed <= 0) {
			playerSP->currentMovementSpeed = 0;
			StopRunning(playerSP);
		}
	}

	void RunPlayerAction::Run(Player::Object::SP playerSP)
	{
		ML::Vec2 targetMove = ML::Vec2(0, 0);

		switch (playerSP->direction) {
			case Direction::Left:	targetMove.x -= playerSP->currentMovementSpeed;		break;
			case Direction::Right:	targetMove.x += playerSP->currentMovementSpeed;		break;
			case Direction::Up:		targetMove.y -= playerSP->currentMovementSpeed;		break;
			case Direction::Down:	targetMove.y += playerSP->currentMovementSpeed;		break;
		}

		playerSP->AdjustMoveWithMap(targetMove);
	}
}