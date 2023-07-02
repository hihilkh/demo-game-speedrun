#pragma once

#include "MapObject.h"

namespace Map
{
	class GoalObject : public MapObject
	{
	public:
		explicit GoalObject(GameObject& gameObject);
	};
}