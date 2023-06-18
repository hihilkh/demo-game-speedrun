#pragma once

#include "GE/Utils/TypeDef.h"

namespace Map
{
	class TransportBeltTile;
}

namespace Prefab::Map
{
	class TransportBeltTilePrefab
	{
	public:
		::Map::TransportBeltTile& operator()(GameObject& baseGameObject) const;
	};
}