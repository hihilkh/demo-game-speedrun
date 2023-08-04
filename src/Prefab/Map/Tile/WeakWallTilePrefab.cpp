#include "GE/GEHeader.h"
#include "WeakWallTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/DataType/Rect.h"
#include "GE/Collision/Collider.h"
#include "GE/Render/Image.h"
#include "GE/Particle/ParticleSystem.h"
#include "Rendering/RenderPriority.h"
#include "GE/Particle/Module/RectEmissionModule.h"
#include "GE/Particle/Module/VelocityModule.h"
#include "GE/Particle/Module/ColorOverLifetimeModule.h"

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
		auto& particleSystem = baseGameObject.AddComponent<ParticleSystem>("./data/ParticleSystem/WeakWallBreak.json");

		return baseGameObject.AddComponent<::Map::WeakWallTile>(*collider, *image, particleSystem);
	}
}