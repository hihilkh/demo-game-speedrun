#include "BasicPlayerAction.h"

namespace Player
{
	BasicPlayerAction::BasicPlayerAction(Player::Object::SP player, XI::GamePad::SP controller) :
		PlayerActionBase::PlayerActionBase(player, controller)
	{

	}

	BasicPlayerAction::~BasicPlayerAction()
	{

	}

	ML::Vec2 BasicPlayerAction::PreMove()
	{
		XI::VGamePad input = controller->GetState();
		return TryWalk(input);
	}
}