#pragma once

#include "PlayerActionBase.h"

namespace Player
{
	class RunPlayerAction : public PlayerActionBase {
	private:
		RunPlayerAction(const RunPlayerAction&) = delete;

	public:
		RunPlayerAction(Player::Object::SP player, XI::GamePad::SP controller);
		~RunPlayerAction();

	private:
		bool isRunning;
		int prepareRunCounter;

	private:
		void StartRunning(Player::Object::SP playerSP);
		void StopRunning(Player::Object::SP playerSP);
		void UpdateRunning(Player::Object::SP playerSP, bool hasInput);
		bool CheckIsPrepareToRun() const;
		void Decelerate(Player::Object::SP playerSP);
		void Run(Player::Object::SP playerSP);

	public:
		PlayerMode GetPlayerMode() const override { return PlayerMode::Run; }
		void UpDate() override;
	};
}