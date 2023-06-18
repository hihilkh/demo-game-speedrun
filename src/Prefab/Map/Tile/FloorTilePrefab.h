#pragma once

#include "GE/Utils/TypeDef.h"

namespace Map
{
	class FloorTile;
}

namespace Prefab::Map
{
	class FloorTilePrefab
	{
	public:
		::Map::FloorTile& operator()(GameObject& baseGameObject) const;
	};
}