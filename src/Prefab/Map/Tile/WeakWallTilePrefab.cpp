#include "GE/GEHeader.h"
#include "WeakWallTilePrefab.h"
#include "TilePrefabUtils.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/DataType/Rect.h"
#include "GE/Collision/Collider.h"
#include "GE/Render/Image.h"
#include "GE/Particle/ParticleSystem.h"
#include "GE/Particle/Module/ImageModule.h"
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

		// ParticleSystem
		GE::Particle::CoreConfig coreConfig(1.0f);
		auto& particleSystem = baseGameObject.AddComponent<ParticleSystem>(coreConfig);

		auto& imageModule = particleSystem.AddModule<GE::Particle::ImageModule>();
		imageModule.SetImage("./data/Image/WallFragment.png", RenderPriority::mapFront);

		auto& rectEmissionModule = particleSystem.AddModule<GE::Particle::RectEmissionModule>();
		rectEmissionModule.SetRect(32.0f, 32.0f);
		rectEmissionModule.SetRotationRange(0.0f, 360.0f);

		auto& velocityModule = particleSystem.AddModule<GE::Particle::VelocityModule>();
		velocityModule.SetEmitAngleRange(0.0f, 360.0f);
		velocityModule.SetEmitSpeedRange(2.0f);
		velocityModule.SetAcceleration(0.0f, -3.0f);

		auto& colorOverLifetimeModule = particleSystem.AddModule<GE::Particle::ColorOverLifetimeModule>();
		colorOverLifetimeModule.SetColor(Color::white, Color(1.0f, 1.0f, 1.0f, 0.0f), GE::Easing::Type::Linear);
		
		return baseGameObject.AddComponent<::Map::WeakWallTile>(*collider, *image, particleSystem);
	}
}