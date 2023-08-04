#include "GE/GEHeader.h"
#include "Tile.h"
#include "Map/MapSizeInfo.h"

namespace Map
{
	Tile::Tile(GameObject& gameObject, TileType type) : 
		Component(gameObject), 
		type(type) 
	{
	}

	void Tile::SetPos(const Vector2Int& grid)
	{
		GetTransform().SetPos(ConvertPosFromGrid(grid));
	}
}