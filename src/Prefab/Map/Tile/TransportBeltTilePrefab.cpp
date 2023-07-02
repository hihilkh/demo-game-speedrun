#include "GE/GEHeader.h"
#include "TransportBeltTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/TransportBeltTile.h"
#include "GE/DataType/Rect.h"
#include "Map/MapSizeInfo.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "TransportBeltTile";
		const RectPixel imgSrcRect(0, ::Map::tileHeight, ::Map::tileWidth, ::Map::tileHeight);	// ダミー
	}

	::Map::TransportBeltTile& TransportBeltTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			imgSrcRect,
			true,				// hasCollider
			true				// isColliderTrigger
		);

		return baseGameObject.AddComponent<::Map::TransportBeltTile>();
	}
}