#include "GE/GEHeader.h"
#include "UnbreakableWallTile.h"

namespace Map
{
	UnbreakableWallTile::UnbreakableWallTile(GameObject& gameObject) :
		TileBase(gameObject, Map::TileType::UnbreakableWall)
	{
	}
}