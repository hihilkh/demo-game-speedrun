#pragma once

#include "TileBase.h"

namespace Map
{
	class WeakWallTile : public TileBase
	{
	public:
		explicit WeakWallTile(GameObject& gameObject);

	private:
		bool isBroken;
	};
}