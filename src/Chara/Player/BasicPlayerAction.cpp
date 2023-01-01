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

	void BasicPlayerAction::UpDate()
	{
		XI::VGamePad input = controller->GetState();
		Move(input);
	}
}