#include "GE/GEHeader.h"
#include "WeakWallTile.h"
#include "GE/Collision/Collider.h"
#include "Map/MapSizeInfo.h"
#include "GE/Render/Image.h"

namespace Map
{
	const RectPixel WeakWallTile::normalImgSrcRect(tileWidth * 2, 0, tileWidth, tileHeight);
	const RectPixel WeakWallTile::brokenImgSrcRect(0, 0, tileWidth, tileHeight);

	WeakWallTile::WeakWallTile(GameObject& gameObject, GE::Collision::Collider& collider, GE::Render::Image& image) :
		Tile(gameObject, Map::TileType::WeakWall),
		isBroken(false),
		collider(collider),
		image(image)
	{
	}

	void WeakWallTile::Break()
	{
		if (isBroken) {
			return;
		}

		isBroken = true;
		collider.SetIsEnable(false);
		image.SetSrcRect(brokenImgSrcRect);

		// TODO : BreakWallEffect
		// 古いコード
		//auto effect = ParticleSystem::BreakWallEffect::Object::Create(true);
		//effect->Play(GetCenterPos(), 20, 60);
	}
}