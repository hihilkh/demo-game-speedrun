#include "GE/GEHeader.h"
#include "PlayerFallbackStateHandler.h"

// TODO
namespace Player
{
	PlayerFallbackStateHandler::PlayerFallbackStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::Fallback)
	{
	}
}

