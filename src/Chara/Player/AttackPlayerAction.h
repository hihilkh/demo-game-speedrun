#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class AttackPlayerAction : public PlayerActionBase {
	private:
		AttackPlayerAction(const AttackPlayerAction&) = delete;

	public:
		AttackPlayerAction(Player::Object::SP player, XI::GamePad::SP controller);
		~AttackPlayerAction();

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Attack; }
		void UpDate() override;
	};
}