﻿#include "GE/GEHeader.h"
#include "TilePrefabUtils.h"
#include "GE/Render/Image.h"
#include "Rendering/RenderPriority.h"
#include "GE/Collision/RectCollider.h"
#include "Collision/CollisionInfo.h"

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

		auto& image = baseGameObject.AddComponent<Image>("./data/Image/MapTile.png", imgSrcRect);
		image.SetRenderPriority(RenderPriority::mapBack);

		if (hasCollider) {
			auto& collider = baseGameObject.AddComponent<RectCollider>(
				isColliderTrigger,
				false,
				Rect::FromCenter((float)imgSrcRect.width, (float)imgSrcRect.height));
			collider.SetCollisionLayer(CollisionInfo::mapLayer);
		}
	}
}
