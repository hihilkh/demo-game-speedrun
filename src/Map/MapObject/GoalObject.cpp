#include "GE/GEHeader.h"
#include "GoalObject.h"
#include "GE/Collision/Collider.h"

namespace Map
{
	GE::Event<> GoalObject::onGoalReached;

	GoalObject::GoalObject(GameObject& gameObject, Collider& collider) :
		MapObject(gameObject, Map::MapObjectType::Goal),
		collider(collider),
		isTriggered(false)
	{
	}

	void GoalObject::Start()
	{
		collider.onTriggered.AddListener(&GoalObject::Trigger, *this);
	}

	void GoalObject::PreDestroy()
	{
		collider.onTriggered.RemoveListener(&GoalObject::Trigger, *this);
	}

	void GoalObject::Trigger(const Collider& other, CollidedType collidedType)
	{
		if (isTriggered) {
			return;
		}

		isTriggered = true;
		onGoalReached.Invoke();
	}
}