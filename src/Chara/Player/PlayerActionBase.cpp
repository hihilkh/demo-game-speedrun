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

	ML::Vec2 PlayerActionBase::TryWalk(const XI::VGamePad& input)
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return ML::Vec2();
		}

		Direction previousDirection = playerSP->direction;
		bool isDirectionFixed = false;
		ML::Vec2 targetMove = ML::Vec2(0, 0);

		auto setPlayer = [&](Direction direction) {
			targetMove += playerSP->GetDirectionalVector(direction) * Constant::WalkSpeed;
			SetDirection(playerSP, previousDirection, direction, isDirectionFixed);
		};

		if (input.LStick.BL.on) { setPlayer(Direction::Left); }
		if (input.LStick.BR.on) { setPlayer(Direction::Right); }
		if (input.LStick.BU.on) { setPlayer(Direction::Up); }
		if (input.LStick.BD.on) { setPlayer(Direction::Down); }

		if (targetMove.x == 0 && targetMove.y == 0) {
			playerSP->currentMovementSpeed = 0;
			playerSP->state = PlayerState::Idle;
		}
		else {
			// AdjustMoveWithMap()の結果に関係なく、inputがあればWalkになる
			playerSP->currentMovementSpeed = Constant::WalkSpeed;
			playerSP->state = PlayerState::Walk;
		}

		return targetMove;
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

	void PlayerActionBase::CollideWithMap()
	{
	}
}