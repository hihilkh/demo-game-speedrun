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
		float currentRunningSpeed;	// playerのcurrentMovementSpeedと違う
		int prepareToRunCounter;

	private:
		ML::Vec2 PrepareToRun(Player::Object::SP playerSP);
		void StopRunning(Player::Object::SP playerSP);
		ML::Vec2 UpdateRunning(Player::Object::SP playerSP, bool hasInput);
		bool CheckIsReadyToRun() const;

		void SetAndApplyRunningSpeed(Player::Object::SP playerSP, float speed);
		void Decelerate(Player::Object::SP playerSP);

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Run; }
		ML::Vec2 PreMove() override;
		void CollidedWithMap(const vector<Direction>& collidedDirections) override;
	};
}