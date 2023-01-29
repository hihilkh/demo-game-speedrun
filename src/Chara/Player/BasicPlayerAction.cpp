#include "BasicPlayerAction.h"

namespace Player
{
	BasicPlayerAction::BasicPlayerAction(Player::Object::WP player) :
		PlayerActionBase::PlayerActionBase(player)
	{

	}

	BasicPlayerAction::~BasicPlayerAction()
	{

	}

	ML::Vec2 BasicPlayerAction::PreMove()
	{
		return TryWalk(GetInput());
	}
}