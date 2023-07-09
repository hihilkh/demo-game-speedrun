#include "GE/GEHeader.h"
#include "PlayerWalkStateHandler.h"
#include "Character/Player/PlayerModel.h"
#include "Character/Player/PlayerConfig.h"

namespace Player
{
	PlayerWalkStateHandler::PlayerWalkStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::Walk)
	{
	}

	void PlayerWalkStateHandler::OnUpdate()
	{
		model.UpdateFacingDirection();

		auto& dirVector = model.GetMoveDirVector();
		Vector2 moveVector = walkSpeed * Time::GetDeltaTime() * dirVector;
		Transform2D& transform = model.GetTransform();
		transform.SetPos(transform.GetPos() + moveVector);
	}
}

