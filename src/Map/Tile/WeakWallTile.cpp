#include "GE/GEHeader.h"
#include "WeakWallTile.h"

// TODO
namespace Map
{
	WeakWallTile::WeakWallTile(GameObject& gameObject) :
		TileBase(gameObject, Map::TileType::WeakWall),
		isBroken(false)
	{
	}
}