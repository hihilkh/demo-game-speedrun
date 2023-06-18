#include "GE/GEHeader.h"
#include "TilePrefabUtils.h"
#include "GE/Render/Image.h"

namespace Prefab::Map::Tile
{
	void CreateCommon(
		GameObject& baseGameObject, 
		const std::string& name, 
		const RectPixel& imgSrcRect,
		bool hasCollider,
		bool isColliderTrigger)
	{
		baseGameObject.SetName(name);

		baseGameObject.AddComponent<GE::Render::Image>("./data/Image/MapTile.png", imgSrcRect);

		// TODO : Collider
	}
}
