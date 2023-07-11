#include "GE/GEHeader.h"
#include "PlayerRunStateHandler.h"
#include "Character/Player/PlayerModel.h"
#include "Character/Player/PlayerConfig.h"

namespace Player
{
	PlayerRunStateHandler::PlayerRunStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::Run)
	{
	}

	void PlayerRunStateHandler::OnUpdate()
	{
		using namespace TransformUtils;

		Direction dir = model.GetFacingDirection();
		Vector2 moveVector = GetDirectionalVector(dir);
		moveVector *= runSpeed * Time::GetDeltaTime();
		Transform2D& transform = model.GetTransform();
		transform.SetPos(transform.GetPos() + moveVector);
	}
}

