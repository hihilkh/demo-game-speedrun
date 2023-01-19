#pragma once

#include "Task_Player.h"
#include "PlayerMode.h"

namespace Player
{
	class PlayerActionBase
	{
	private:
		PlayerActionBase(const PlayerActionBase&) = delete;

	protected:
		PlayerActionBase(Player::Object::WP player, XI::GamePad::SP controller);

	public:
		virtual ~PlayerActionBase();

	protected:
		Player::Object::WP player;
		XI::GamePad::SP controller;
	
	private:
		void SetDirection(Player::Object::SP playerSP, Direction previousDirection, Direction targetDirection, bool& isDirectionFixed);

	protected:
		ML::Vec2 TryWalk(const XI::VGamePad& input);

	public:
		virtual PlayerMode GetPlayerMode() const = 0;
		virtual ML::Vec2 PreMove() = 0;
		virtual void CollideWithMap();
	};
}