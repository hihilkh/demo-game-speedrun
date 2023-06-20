#pragma once

#include "Tile.h"

namespace Map
{
	class WeakWallTile : public Tile
	{
	public:
		explicit WeakWallTile(GameObject& gameObject);

	private:
		bool isBroken;
	};
}