#pragma once

#include "TileBase.h"

namespace Map
{
	class UnbreakableWallTile : public TileBase
	{
	public:
		explicit UnbreakableWallTile(GameObject& gameObject);
	};
}