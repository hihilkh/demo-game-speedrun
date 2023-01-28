#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class AttackPlayerAction : public PlayerActionBase {
	private:
		AttackPlayerAction(const AttackPlayerAction&) = delete;

	public:
		explicit AttackPlayerAction(Player::Object::WP player);
		~AttackPlayerAction();

	private:
		void OnAnimFinished(PlayerState finishedState);

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Attack; }
		ML::Vec2 PreMove() override;
	};
}