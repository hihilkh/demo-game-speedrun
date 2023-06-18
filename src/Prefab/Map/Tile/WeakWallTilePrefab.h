#pragma once

#include "GE/Utils/TypeDef.h"

namespace Map
{
	class WeakWallTile;
}

namespace Prefab::Map
{
	class WeakWallTilePrefab
	{
	public:
		::Map::WeakWallTile& operator()(GameObject& baseGameObject) const;
	};
}