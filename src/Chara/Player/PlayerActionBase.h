#pragma once

#include "Task_Player.h"
#include "PlayerMode.h"

// TODO : PlayerActionとPlayerControllerを分ける
namespace Player
{
	class PlayerActionBase
	{
	private:
		PlayerActionBase(const PlayerActionBase&) = delete;

	protected:
		explicit PlayerActionBase(Player::Object::WP player);

	public:
		virtual ~PlayerActionBase();

	protected:
		Player::Object::WP player;
	
	private:
		void SetDirection(Player::Object::SP playerSP, Direction previousDirection, Direction targetDirection, bool& isDirectionFixed);

	protected:
		ML::Vec2 TryWalk(const XI::VGamePad& input);
		bool CheckIsAllowInput() const;
		XI::VGamePad GetInput() const;

	public:
		virtual PlayerMode GetPlayerMode() const = 0;
		virtual ML::Vec2 PreMove() = 0;
		virtual void CollideWithMap() {}
	};
}