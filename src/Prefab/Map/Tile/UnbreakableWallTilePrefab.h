#pragma once

#include "GE/Utils/TypeDef.h"

namespace Map
{
	class UnbreakableWallTile;
}

namespace Prefab::Map
{
	class UnbreakableWallTilePrefab
	{
	public:
		::Map::UnbreakableWallTile& operator()(GameObject& baseGameObject) const;
	};
}