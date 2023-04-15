#include "AttackPlayerAction.h"
#include "Debug/Log.h"
#include "PlayerAnimator.h"

namespace Player
{
	AttackPlayerAction::AttackPlayerAction(Player::Object::WP player) :
		PlayerActionBase::PlayerActionBase(player)
	{
		if (auto playerSP = player.lock()) {
			playerSP->animator->animFinished.AddListener(this, &AttackPlayerAction::OnAnimFinished);
		}
	}

	AttackPlayerAction::~AttackPlayerAction()
	{
		if (auto playerSP = player.lock()) {
			playerSP->animator->animFinished.RemoveListeners(this);
		}
	}

	ML::Vec2 AttackPlayerAction::PreMove()
	{
		auto playerSP = player.lock();
		if (!playerSP) {
			DEBUG_LOG_WARNING("プレイヤーの参照が取れない");
			return ML::Vec2();
		}

		XI::VGamePad input = GetInput();

		if (playerSP->state == PlayerState::Attack) {
			return ML::Vec2();
		}

		if (input.B2.down) {
			playerSP->state = PlayerState::Attack;
			return ML::Vec2();
		}

		return TryWalk(input);
	}

	void AttackPlayerAction::OnAnimFinished(PlayerState finishedState)
	{
		if (finishedState == PlayerState::Attack) {
			auto playerSP = player.lock();
			if (!playerSP) {
				DEBUG_LOG_WARNING("プレイヤーの参照が取れない");
				return;
			}

			playerSP->state = PlayerState::Idle;
		}
	}
}