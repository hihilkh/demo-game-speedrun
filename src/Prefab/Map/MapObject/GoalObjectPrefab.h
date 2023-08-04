#pragma once

#include "GE/Utils/TypeDef.h"

namespace Map
{
	class GoalObject;
}

namespace Prefab::Map
{
	class GoalObjectPrefab
	{
	public:
		::Map::GoalObject& operator()(GameObject& baseGameObject) const;
	};
}