#include "PlayerActionBase.h"

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
		ML::Vec2 targetMove = ML::Vec2(0, 0);

		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			return;
		}

		if (input.LStick.BL.on) { targetMove.x -= playerSP->speed; playerSP->direction = Player::Object::Direction::Left; }
		if (input.LStick.BR.on) { targetMove.x += playerSP->speed; playerSP->direction = Player::Object::Direction::Right; }
		if (input.LStick.BU.on) { targetMove.y -= playerSP->speed; }
		if (input.LStick.BD.on) { targetMove.y += playerSP->speed; }

		playerSP->AdjustMoveWithMap(targetMove);
	}
}