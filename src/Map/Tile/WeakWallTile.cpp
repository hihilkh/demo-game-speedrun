#include "GE/GEHeader.h"
#include "WeakWallTile.h"
#include "GE/Collision/Collider.h"
#include "Map/MapSizeInfo.h"
#include "GE/Render/Image.h"
#include "GE/Particle/ParticleSystem.h"

namespace Map
{
	const RectPixel WeakWallTile::normalImgSrcRect(tileWidth * 2, 0, tileWidth, tileHeight);
	const RectPixel WeakWallTile::brokenImgSrcRect(0, 0, tileWidth, tileHeight);

	WeakWallTile::WeakWallTile(GameObject& gameObject, Collider& collider, Image& image, ParticleSystem& particleSystem) :
		Tile(gameObject, Map::TileType::WeakWall),
		isBroken(false),
		collider(collider),
		image(image),
		particleSystem(particleSystem)
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

		particleSystem.Play();
	}
}