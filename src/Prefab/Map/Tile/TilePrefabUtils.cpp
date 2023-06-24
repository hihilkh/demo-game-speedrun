#include "GE/GEHeader.h"
#include "TilePrefabUtils.h"
#include "GE/Render/Image.h"
#include "Common/RenderPriority.h"
#include "GE/Physics/RectCollider.h"

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
		baseGameObject.SetIsStatic(true);

		auto& image = baseGameObject.AddComponent<GE::Render::Image>("./data/Image/MapTile.png", imgSrcRect);
		image.SetRenderPriority(RenderPriority::mapBack);

		if (hasCollider) {
			baseGameObject.AddComponent<GE::Physics::RectCollider>(
				isColliderTrigger, 
				Rect::FromCenter((float)imgSrcRect.width, (float)imgSrcRect.height));
		}
	}
}
