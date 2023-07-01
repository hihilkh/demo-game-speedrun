#pragma once

#include "../DetectorImpl.h"
#include "CollisionRecordHandler.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	class NonRotatedRectSimpleDetectorImpl : public DetectorImpl
	{
	public:
		NonRotatedRectSimpleDetectorImpl();

		void RecordCollision(CollisionRecord&& record) override;
		Vector2 GetCollisionAdjustmentPosOffset() override;

		// Rect <-> Rect
		CollidedType CheckAndRecordCollision(
			const RectCollider& lhs,
			const RectCollider& rhs,
			RectDetector& lhsDetector,
			RectDetector& rhsDetector) override;

		CollidedType CheckCollision(
			const Rect& lhsRect,
			const Rect& rhsRect,
			float lhsRot,
			float rhsRot) const override;

	private:
		CollisionRecordHandler collisionRecordHandler;
	};
}