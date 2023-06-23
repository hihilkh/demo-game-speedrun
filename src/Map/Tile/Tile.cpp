#include "GE/GEHeader.h"
#include "Tile.h"
#include "TileRenderInfo.h"

namespace Map
{
	Tile::Tile(GameObject& gameObject, TileType type) : 
		Component(gameObject), 
		type(type) 
	{
	}

	void Tile::SetPos(const Vector2Int& pos)
	{
		GetTransform().pos.x = (float)(tileWidth * pos.x);
		GetTransform().pos.y = (float)(tileHeight * pos.y);
	}
}