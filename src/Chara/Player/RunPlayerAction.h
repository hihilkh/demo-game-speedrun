#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class RunPlayerAction : public PlayerActionBase {
	private:
		RunPlayerAction(const RunPlayerAction&) = delete;

	public:
		explicit RunPlayerAction(Player::Object::WP player);
		~RunPlayerAction();

	private:
		bool isRunning;
		int prepareRunCounter;

	private:
		ML::Vec2 StartRunning(Player::Object::SP playerSP);
		void StopRunning(Player::Object::SP playerSP);
		ML::Vec2 UpdateRunning(Player::Object::SP playerSP, bool hasInput);
		bool CheckIsPrepareToRun() const;
		void Decelerate(Player::Object::SP playerSP);

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Run; }
		ML::Vec2 PreMove() override;
		void CollideWithMap() override;
	};
}