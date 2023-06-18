#pragma once

#include "TileBase.h"

namespace Map
{
	class FloorTile : public TileBase
	{
	public:
		explicit FloorTile(GameObject& gameObject);
	};
}