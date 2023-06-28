#pragma once

#include "Detector.h"
#include "SimpleImpl/Detection.h"
#include "SimpleImpl/CollisionAdjustmentInfo.h"

namespace GE::Physics::CollisionDetection
{
	class RectDetector : public Detector
	{
	public:
		CollidedType CheckCollision(const RectCollider& other) const override
		{
			return SimpleImpl::CheckCollision(GetSelfCollider(), other);
		}
		void RecordCollisionAdjustment(RectCollider& other) override
		{
			return SimpleImpl::RecordCollisionAdjustment(GetSelfCollider(), other);
		}

		Vector2 GetCollisionAdjustmentPosOffset() override
		{
			return adjustmentInfo.CalculateAdjustmentAndClearInfos();
		}

		void AddAdjustmentInfo(float xOffset, float yOffset)
		{
			adjustmentInfo.AddInfo(xOffset, yOffset);
		}

	private:
		SimpleImpl::CollisionAdjustmentInfo adjustmentInfo;

	private:
		virtual RectCollider& GetSelfCollider() = 0;
		virtual const RectCollider& GetSelfCollider() const = 0;
	};
}