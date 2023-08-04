#pragma once

#include "Tile.h"

namespace Map
{
	class FloorTile : public Tile
	{
	public:
		explicit FloorTile(GameObject& gameObject);
	};
}