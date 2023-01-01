#pragma once

#include "PlayerActionBase.h"
#include "Utils/Log.h"

namespace Player
{
	class BasicPlayerAction : public PlayerActionBase {

	public:
		BasicPlayerAction(Player::Object::SP player, XI::GamePad::SP controller);
		~BasicPlayerAction();

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Basic; }
		void UpDate() override;
	};
}