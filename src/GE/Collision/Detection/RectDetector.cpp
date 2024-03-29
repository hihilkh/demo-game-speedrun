﻿#include "RectDetector.h"
#include "DetectorFactory.h"
#include "DetectorImpl.h"

namespace GE::Collision::Detection
{
	RectDetector::RectDetector(const RectCollider& collider) :
		pImpl(GenerateDetectorImpl()),
		collider(collider)
	{
	}

	RectDetector::~RectDetector() = default;

	CollidedType RectDetector::CheckCollision(const RectCollider& other, RectDetector& otherDetector)
	{
		return pImpl->CheckAndRecordCollision(collider, other, *this, otherDetector);
	}

	void RectDetector::RecordCollision(CollisionRecord&& record)
	{
		pImpl->RecordCollision(std::move(record));
	}

	Vector2 RectDetector::GetCollisionAdjustmentPosOffset()
	{
		return pImpl->GetCollisionAdjustmentPosOffset();
	}
}