#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class BasicPlayerAction : public PlayerActionBase {
	private:
		BasicPlayerAction(const PlayerActionBase&) = delete;

	public:
		BasicPlayerAction(Player::Object::SP player, XI::GamePad::SP controller);
		~BasicPlayerAction();

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Basic; }
		void UpDate() override;
	};
}