#include "GE/GEHeader.h"
#include "UnbreakableWallTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/UnbreakableWallTile.h"
#include "GE/DataType/Rect.h"
#include "Map/Tile/TileRenderInfo.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "UnbreakableWallTile";
		const RectPixel imgSrcRect(::Map::tileWidth, 0, ::Map::tileWidth, ::Map::tileHeight);
	}

	::Map::UnbreakableWallTile& UnbreakableWallTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			imgSrcRect,
			true,				// hasCollider
			false				// isColliderTrigger
		);

		return baseGameObject.AddComponent<::Map::UnbreakableWallTile>();
	}
}