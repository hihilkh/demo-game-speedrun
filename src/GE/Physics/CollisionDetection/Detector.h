#pragma once

#include "ColliderTypeDef.h"
#include "CollidedType.h"

namespace GE::Physics::CollisionDetection
{
	class Detector
	{
	public:
		virtual ~Detector() = default;

#pragma region Visitorパターン

		virtual CollidedType CheckCollision(const RectCollider& other) const { return CollidedType::None; }
		virtual void RecordCollisionAdjustment(RectCollider& other) {}

#pragma endregion

		virtual Vector2 GetCollisionAdjustmentPosOffset() = 0;
	};
}