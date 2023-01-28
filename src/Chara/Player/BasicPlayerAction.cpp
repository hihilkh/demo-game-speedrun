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
		XI::VGamePad input = ge->in1->GetState();
		return TryWalk(input);
	}
}