#include "GE/GEHeader.h"
#include "PlayerStopRunningStateHandler.h"
#include "Character/Player/PlayerModel.h"
#include "Character/Player/PlayerConfig.h"

namespace Player
{
	PlayerStopRunningStateHandler::PlayerStopRunningStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::StopRunning),
		currentSpeed(0.0f)
	{
	}

	void PlayerStopRunningStateHandler::OnEnter()
	{
		currentSpeed = runSpeed;
	}

	void PlayerStopRunningStateHandler::OnUpdate()
	{
		// TODO : 壁と当たっる（fallbackではないとき）と、すぐStopRunning済みになる
		if (currentSpeed <= 0.0f) {
			return;
		}

		currentSpeed -= runDeceleration * Time::GetDeltaTime();
		if (currentSpeed < 0.0f) {
			currentSpeed = 0.0f;
			return;
		}

		using namespace TransformUtils;

		Direction dir = model.GetFacingDirection();
		Vector2 dirVector = GetDirectionalVector(dir);
		Vector2 moveVector = currentSpeed * Time::GetDeltaTime() * dirVector;
		Transform2D& transform = model.GetTransform();
		transform.SetPos(transform.GetPos() + moveVector);
	}

	void PlayerStopRunningStateHandler::OnExit()
	{
	}

	bool PlayerStopRunningStateHandler::CheckHasDoneState()
	{
		return currentSpeed <= 0.0f;
	}
}

