#include "GE/GEHeader.h"
#include "WeakWallTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/DataType/Rect.h"
#include "GE/Collision/Collider.h"
#include "GE/Render/Image.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "WeakWallTile";
	}

	::Map::WeakWallTile& WeakWallTilePrefab::operator()(GameObject& baseGameObject) const
	{
		Tile::CreateCommon(
			baseGameObject,
			objName,
			::Map::WeakWallTile::normalImgSrcRect,
			true,				// hasCollider
			false				// isColliderTrigger
		);

		auto collider = baseGameObject.GetComponent<Collider>();
		auto image = baseGameObject.GetComponent<Image>();

		return baseGameObject.AddComponent<::Map::WeakWallTile>(*collider, *image);
	}
}