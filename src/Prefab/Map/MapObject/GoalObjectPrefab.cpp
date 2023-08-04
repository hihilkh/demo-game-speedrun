#include "GE/GEHeader.h"
#include "GoalObjectPrefab.h"
#include "Map/MapObject/GoalObject.h"
#include "GE/DataType/Rect.h"
#include "GE/Render/Image.h"
#include "Rendering/RenderPriority.h"
#include "GE/Collision/RectCollider.h"
#include "Collision/CollisionInfo.h"
#include "Map/MapSizeInfo.h"
#include "GE/Animation/Animator.h"

namespace Prefab::Map
{
	namespace
	{
		const std::string objName = "GoalObject";
		const RectPixel imgSrcRect(0, 0, ::Map::tileWidth, ::Map::tileHeight);
		const Rect colliderRect = Rect::FromCenter(::Map::tileWidth * 0.4f, ::Map::tileHeight * 0.8f);
	}

	::Map::GoalObject& GoalObjectPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName(objName);

		auto& offsetBase = baseGameObject.AddChild("OffsetBase");
		offsetBase.GetTransform().SetPosY(::Map::tileHeight / 4);

		auto& image = offsetBase.AddComponent<Image>("./data/Image/Flag.png", imgSrcRect);
		image.SetRenderPriority(RenderPriority::mapObject);

		auto& collider = offsetBase.AddComponent<RectCollider>(
			true,
			false,
			colliderRect);
		collider.SetCollisionLayer(CollisionInfo::mapLayer);

		auto& animator = baseGameObject.AddComponent<Animator>("./data/Animation/GoalObject.json");
		animator.SetImage(&image);

		return baseGameObject.AddComponent<::Map::GoalObject>(collider);
	}
}