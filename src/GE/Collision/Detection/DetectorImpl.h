#pragma once

#include "CollidedType.h"
#include "../ColliderTypeDef.h"
#include "DetectorTypeDef.h"
#include "GE/Utils/TypeDef.h"

namespace GE::Collision::Detection
{
	struct CollisionRecord;

	class DetectorImpl
	{
	public:
		virtual ~DetectorImpl() = default;

		virtual void RecordCollision(const CollisionRecord& record) = 0;
		virtual Vector2 GetCollisionAdjustmentPosOffset() = 0;

		// Rect <-> Rect
		virtual CollidedType CheckAndRecordCollision(
			const RectCollider& lhs, 
			const RectCollider& rhs, 
			RectDetector& lhsDetector, 
			RectDetector& rhsDetector)
		{ 
			return CollidedType::None; 
		}

		virtual CollidedType CheckCollision(
			const Rect& lhsRect, 
			const Rect& rhsRect, 
			float lhsRot, 
			float rhsRot) const 
		{ 
			return CollidedType::None; 
		}

	};
}