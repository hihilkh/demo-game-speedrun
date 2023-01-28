#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class BasicPlayerAction : public PlayerActionBase {
	private:
		BasicPlayerAction(const BasicPlayerAction&) = delete;

	public:
		explicit BasicPlayerAction(Player::Object::WP player);
		~BasicPlayerAction();

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Basic; }
		ML::Vec2 PreMove() override;
	};
}