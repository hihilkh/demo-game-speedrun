#include "AttackPlayerAction.h"
#include "Utils/Log.h"

namespace Player
{
	AttackPlayerAction::AttackPlayerAction(Player::Object::SP player, XI::GamePad::SP controller) :
		PlayerActionBase::PlayerActionBase(player, controller)
	{

	}

	AttackPlayerAction::~AttackPlayerAction()
	{

	}

	void AttackPlayerAction::UpDate()
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return;
		}

		XI::VGamePad input = controller->GetState();

		if (playerSP->state == PlayerState::Attack) {
			return;
		}

		if (input.ST.down) {
			playerSP->state = PlayerState::Attack;
			return;
		}

		Move(input);
	}
}