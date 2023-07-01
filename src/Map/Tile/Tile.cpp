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
		GetTransform().SetPos(
			(float)(tileWidth * pos.x), 
			(float)(tileHeight * pos.y)
		);
	}
}