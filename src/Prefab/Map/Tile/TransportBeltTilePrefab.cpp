#include "GE/GEHeader.h"
#include "TransportBeltTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/TransportBeltTile.h"
#include "GE/DataType/Rect.h"
#include "Map/MapSizeInfo.h"
#include "GE/Collision/Collider.h"
#include "GE/Render/Image.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "TransportBeltTile";
	}

	::Map::TransportBeltTile& TransportBeltTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			::Map::TransportBeltTile::downImgSrcRect,
			true,				// hasCollider
			true				// isColliderTrigger
		);

		auto collider = baseGameObject.GetComponent<GE::Collision::Collider>();
		auto image = baseGameObject.GetComponent<GE::Render::Image>();

		return baseGameObject.AddComponent<::Map::TransportBeltTile>(*collider, *image);
	}
}