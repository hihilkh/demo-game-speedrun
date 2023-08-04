#pragma once

#include "Tile.h"

namespace Map
{
	class UnbreakableWallTile : public Tile
	{
	public:
		explicit UnbreakableWallTile(GameObject& gameObject);
	};
}