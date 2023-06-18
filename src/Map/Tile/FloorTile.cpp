#include "GE/GEHeader.h"
#include "FloorTile.h"

namespace Map
{
	FloorTile::FloorTile(GameObject& gameObject) :
		TileBase(gameObject, Map::TileType::Floor)
	{
	}
}