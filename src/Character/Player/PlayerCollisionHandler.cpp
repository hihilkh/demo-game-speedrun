#include "GE/GEHeader.h"
#include "PlayerCollisionHandler.h"
#include "GE/Collision/Collider.h"
#include "PlayerModel.h"

namespace Player
{
	PlayerCollisionHandler::PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, GE::Collision::Collider& collider) :
		Component(gameObject),
		model(model),
		collider(collider)
	{
	}

	void PlayerCollisionHandler::Start()
	{
		collider.onCollided.AddListener(&PlayerCollisionHandler::HandleCollision, *this);
	}

	void PlayerCollisionHandler::PreDestroy()
	{
		collider.onCollided.RemoveListener(&PlayerCollisionHandler::HandleCollision, *this);
	}

	void PlayerCollisionHandler::HandleCollision(const GE::Collision::Collider& other)
	{
		if (CheckIsCrash(other)) {
			model.Crash();
		}
	}

	bool PlayerCollisionHandler::CheckIsCrash(const GE::Collision::Collider& other) const
	{
		// TODO
		return true;
	}
}