#include "DetectorImpl.h"
#include "../DetectorFactory.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	NonRotatedRectSimpleDetectorImpl::NonRotatedRectSimpleDetectorImpl() :
		collisionRecordHandler()
	{
	}

	void NonRotatedRectSimpleDetectorImpl::RecordCollision(CollisionRecord&& record)
	{
		collisionRecordHandler.AddRecord(std::move(record));
	}

	Vector2 NonRotatedRectSimpleDetectorImpl::GetCollisionAdjustmentPosOffset()
	{
		return collisionRecordHandler.CalculateAdjustmentAndClearRecords();
	}
}