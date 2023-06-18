#include "GE/GEHeader.h"
#include "TilePrefabUtils.h"
#include "GE/Render/Image.h"
#include "Common/RenderPriority.h"

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

		auto& image = baseGameObject.AddComponent<GE::Render::Image>("./data/Image/MapTile.png", imgSrcRect);
		image.SetRenderPriority(RenderPriority::mapBack);

		// TODO : Collider
	}
}
