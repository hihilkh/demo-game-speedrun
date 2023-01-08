#include "PlayerActionBase.h"
#include "Utils/Log.h"
#include "PlayerConstant.h"

namespace Player
{
	PlayerActionBase::PlayerActionBase(Player::Object::WP player, XI::GamePad::SP controller) :
		player(player),
		controller(controller)
	{
	}

	PlayerActionBase::~PlayerActionBase() 
	{
	}

	void PlayerActionBase::Move(const XI::VGamePad& input)
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return;
		}

		Direction previousDirection = playerSP->direction;
		bool isDirectionFixed = false;
		ML::Vec2 targetMove = ML::Vec2(0, 0);
		if (input.LStick.BL.on) { targetMove.x -= PlayerConstant::WalkSpeed; SetDirection(playerSP, previousDirection, Direction::Left, isDirectionFixed); }
		if (input.LStick.BR.on) { targetMove.x += PlayerConstant::WalkSpeed; SetDirection(playerSP, previousDirection, Direction::Right, isDirectionFixed); }
		if (input.LStick.BU.on) { targetMove.y -= PlayerConstant::WalkSpeed; SetDirection(playerSP, previousDirection, Direction::Up, isDirectionFixed); }
		if (input.LStick.BD.on) { targetMove.y += PlayerConstant::WalkSpeed; SetDirection(playerSP, previousDirection, Direction::Down, isDirectionFixed); }

		if (targetMove.x == 0 && targetMove.y == 0) {
			playerSP->currentMovementSpeed = 0;
			playerSP->state = PlayerState::Idle;
		}
		else {
			// AdjustMoveWithMap()の結果に関係なく、inputがあればWalkになる
			playerSP->currentMovementSpeed = PlayerConstant::WalkSpeed;
			playerSP->state = PlayerState::Walk;
			playerSP->AdjustMoveWithMap(targetMove);
		}
	}

	/// <summary>
	/// できれば、元のDirectionを維持する
	/// </summary>
	void PlayerActionBase::SetDirection(Player::Object::SP playerSP, Direction previousDirection, Direction targetDirection, bool& isDirectionFixed)
	{
		if (isDirectionFixed) {
			return;
		}

		playerSP->direction = targetDirection;
		if (previousDirection == targetDirection) {
			isDirectionFixed = true;
		}
	}
}