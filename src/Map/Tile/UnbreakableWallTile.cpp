#include "GE/GEHeader.h"
#include "UnbreakableWallTile.h"

namespace Map
{
	UnbreakableWallTile::UnbreakableWallTile(GameObject& gameObject) :
		Tile(gameObject, Map::TileType::UnbreakableWall)
	{
	}
}