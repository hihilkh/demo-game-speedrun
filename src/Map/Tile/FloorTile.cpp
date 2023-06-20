#include "GE/GEHeader.h"
#include "FloorTile.h"

namespace Map
{
	FloorTile::FloorTile(GameObject& gameObject) :
		Tile(gameObject, Map::TileType::Floor)
	{
	}
}