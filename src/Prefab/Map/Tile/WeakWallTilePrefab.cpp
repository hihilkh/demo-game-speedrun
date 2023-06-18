#include "GE/GEHeader.h"
#include "WeakWallTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/DataType/Rect.h"
#include "Map/Tile/TileSize.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "WeakWallTile";
		const RectPixel imgSrcRect(::Map::tileWidth * 2, 0, ::Map::tileWidth, ::Map::tileHeight);
	}

	::Map::WeakWallTile& WeakWallTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			imgSrcRect,
			true,				// hasCollider
			false				// isColliderTrigger
		);

		return baseGameObject.AddComponent<::Map::WeakWallTile>();
	}
}