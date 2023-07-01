#pragma once

#include "CollidedType.h"
#include "../ColliderTypeDef.h"
#include "DetectorTypeDef.h"
#include "GE/Utils/TypeDef.h"

namespace GE::Collision::Detection
{
	struct CollisionRecord;

	class Detector
	{
	public:
		virtual ~Detector() = default;

		// Visitorパターン
		virtual CollidedType CheckCollision(const RectCollider& other, RectDetector& otherDetector) { return CollidedType::None; }

		virtual void RecordCollision(CollisionRecord&& record) = 0;
		virtual Vector2 GetCollisionAdjustmentPosOffset() = 0;
	};
}