#include "GE/GEHeader.h"
#include "FloorTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/FloorTile.h"
#include "GE/DataType/Rect.h"
#include "Map/Tile/TileSize.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "FloorTile";
		const RectPixel imgSrcRect(0, 0, ::Map::tileWidth, ::Map::tileHeight);
	}

	::Map::FloorTile& FloorTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject, 
			objName,
			imgSrcRect,
			false,				// hasCollider
			false				// isColliderTrigger
		);

		return baseGameObject.AddComponent<::Map::FloorTile>();
	}
}