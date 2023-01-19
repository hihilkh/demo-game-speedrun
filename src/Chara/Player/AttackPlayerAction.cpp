#include "AttackPlayerAction.h"
#include "Utils/Log.h"
#include "PlayerAnimator.h"

namespace Player
{
	AttackPlayerAction::AttackPlayerAction(Player::Object::SP player, XI::GamePad::SP controller) :
		PlayerActionBase::PlayerActionBase(player, controller)
	{
		player->animator->animFinished.AddListener(this, &AttackPlayerAction::OnAnimFinished);
	}

	AttackPlayerAction::~AttackPlayerAction()
	{
		Player::Object::SP playerSP = player.lock();
		if (playerSP) {
			playerSP->animator->animFinished.RemoveListeners(this);
		}
	}

	ML::Vec2 AttackPlayerAction::PreMove()
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return ML::Vec2();
		}

		XI::VGamePad input = controller->GetState();

		if (playerSP->state == PlayerState::Attack) {
			return ML::Vec2();
		}

		if (input.ST.down) {
			playerSP->state = PlayerState::Attack;
			return ML::Vec2();
		}

		return TryWalk(input);
	}

	void AttackPlayerAction::OnAnimFinished(PlayerState finishedState)
	{
		if (finishedState == PlayerState::Attack) {
			Player::Object::SP playerSP = player.lock();
			if (!playerSP) {
				PrintWarning("プレイヤーの参照が取れない");
				return;
			}

			playerSP->state = PlayerState::Idle;
		}
	}
}