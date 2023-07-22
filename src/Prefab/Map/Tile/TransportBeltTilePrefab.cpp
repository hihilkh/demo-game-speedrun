#include "GE/GEHeader.h"
#include "TransportBeltTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/TransportBeltTile.h"
#include "Map/Tile/TransportBeltAnimationDecision.h"
#include "GE/DataType/Rect.h"
#include "Map/MapSizeInfo.h"
#include "GE/Collision/Collider.h"
#include "GE/Render/Image.h"
#include "GE/Animation/Animator.h"
#include "Map/MapSizeInfo.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "TransportBeltTile";
		const RectPixel dummyImgSrcRect(0, 0, ::Map::tileWidth, ::Map::tileHeight);
	}

	::Map::TransportBeltTile& TransportBeltTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			dummyImgSrcRect,
			true,				// hasCollider
			true				// isColliderTrigger
		);

		auto collider = baseGameObject.GetComponent<Collider>();
		auto image = baseGameObject.GetComponent<Image>();
		auto& tile = baseGameObject.AddComponent<::Map::TransportBeltTile>(*collider);
		auto& animator = baseGameObject.AddComponent<Animator>(
			"./data/Animation/TransportBeltTile.json",
			std::make_unique<::Map::TransportBeltAnimationDecision>(tile));
		animator.SetImage(image);

		return tile;
	}
}