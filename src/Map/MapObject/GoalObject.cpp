#include "GE/GEHeader.h"
#include "GoalObject.h"

namespace Map
{
	GoalObject::GoalObject(GameObject& gameObject) :
		MapObject(gameObject, Map::MapObjectType::Goal)
	{
	}

	// TODO : Animation
}