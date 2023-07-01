#include "DetectorImpl.h"
#include "../DetectorFactory.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	NonRotatedRectSimpleDetectorImpl::NonRotatedRectSimpleDetectorImpl() :
		collisionRecordHandler()
	{
	}

	void NonRotatedRectSimpleDetectorImpl::RecordCollision(const CollisionRecord& record)
	{
		collisionRecordHandler.AddRecord(record);
	}

	Vector2 NonRotatedRectSimpleDetectorImpl::GetCollisionAdjustmentPosOffset()
	{
		return collisionRecordHandler.CalculateAdjustmentAndClearRecords();
	}
}