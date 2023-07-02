﻿#include "DetectorImpl.h"
#include "GE/Collision/RectCollider.h"
#include "GE/DataType/Vector2.h"
#include "GE/Core/Transform2D.h"
#include "GE/Debug/Log.h"
#include "../DetectorFactory.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{

#pragma region RecordCollision

	namespace
	{
		enum class AdjustDir { Left, Right, Up, Down };

		AdjustDir OppositeDir(AdjustDir dir)
		{
			switch (dir) {
				case AdjustDir::Left:	return AdjustDir::Right;
				case AdjustDir::Right:	return AdjustDir::Left;
				case AdjustDir::Up:		return AdjustDir::Down;
				case AdjustDir::Down:	return AdjustDir::Up;
			}

			// 警告を出さないように
			return AdjustDir::Left;
		}

		float GetDeltaPos(const Rect& targetRect, const Rect& otherRect, AdjustDir dir)
		{
			switch (dir) {
				case AdjustDir::Left:	return otherRect.x - targetRect.x - targetRect.width;
				case AdjustDir::Right:	return otherRect.x + otherRect.width - targetRect.x;
				case AdjustDir::Up:		return otherRect.y + otherRect.height - targetRect.y;
				case AdjustDir::Down:	return otherRect.y - targetRect.y - targetRect.height;

			}

			// 警告を出さないように
			return 0.0f;
		}

		void CalculateAndRecordCollision(
			const RectCollider& lhs,
			const RectCollider& rhs,
			const Rect& lhsRect,
			const Rect& rhsRect,
			RectDetector& lhsDetector,
			RectDetector& rhsDetector)
		{
			// この実装は回転を無視する

			if (!lhs.GetIsApplyCollisionAdjustment() && !rhs.GetIsApplyCollisionAdjustment()) {
				return;
			}

			Vector2 vectorFromTwoCenter = rhsRect.Center() - lhsRect.Center();

			AdjustDir rhsAdjustDirX = vectorFromTwoCenter.x > 0 ? AdjustDir::Right : AdjustDir::Left;
			AdjustDir rhsAdjustDirY = vectorFromTwoCenter.y > 0 ? AdjustDir::Up : AdjustDir::Down;

			if (!lhs.GetIsApplyCollisionAdjustment()) {
				float deltaPosX = GetDeltaPos(rhsRect, lhsRect, rhsAdjustDirX);
				float deltaPosY = GetDeltaPos(rhsRect, lhsRect, rhsAdjustDirY);

				rhsDetector.RecordCollision(CollisionRecord({ deltaPosX , deltaPosY }));
			} else if (!rhs.GetIsApplyCollisionAdjustment()) {
				float deltaPosX = GetDeltaPos(lhsRect, rhsRect, OppositeDir(rhsAdjustDirX));
				float deltaPosY = GetDeltaPos(lhsRect, rhsRect, OppositeDir(rhsAdjustDirY));

				lhsDetector.RecordCollision(CollisionRecord({ deltaPosX , deltaPosY }));
			} else {
				float deltaPosX = GetDeltaPos(rhsRect, lhsRect, rhsAdjustDirX) / 2.0f;
				float deltaPosY = GetDeltaPos(rhsRect, lhsRect, rhsAdjustDirY) / 2.0f;

				lhsDetector.RecordCollision(CollisionRecord({ -deltaPosX , -deltaPosY }));
				rhsDetector.RecordCollision(CollisionRecord({ deltaPosX , deltaPosY }));
			}
		}
	}


#pragma endregion

	CollidedType NonRotatedRectSimpleDetectorImpl::CheckAndRecordCollision(
		const RectCollider& lhs,
		const RectCollider& rhs,
		RectDetector& lhsDetector,
		RectDetector& rhsDetector)
	{
		Transform2DData lhsTransformData = lhs.GetTransform().GetWorldTransformData();
		Transform2DData rhsTransformData = rhs.GetTransform().GetWorldTransformData();

		Rect lhsRect = lhs.GetRect();
		lhsRect.Move(lhsTransformData.pos);
		Rect rhsRect = rhs.GetRect();
		rhsRect.Move(rhsTransformData.pos);

		CollidedType collidedType = CheckCollision(
			lhsRect,
			rhsRect,
			lhsTransformData.rot,
			rhsTransformData.rot);

		if (collidedType == CollidedType::Overlap) {
			if (!lhs.GetIsTrigger() && !rhs.GetIsTrigger()) {
				CalculateAndRecordCollision(lhs, rhs, lhsRect, rhsRect, lhsDetector, rhsDetector);
			}
		}

		return collidedType;
	}

	CollidedType NonRotatedRectSimpleDetectorImpl::CheckCollision(
		const Rect& lhsRect,
		const Rect& rhsRect,
		float lhsRot,
		float rhsRot) const
	{
		// この実装はlhsRotとrhsRotを無視する

#ifdef _DEBUG
		if (lhsRot != 0 || rhsRot != 0) {
			DEBUG_LOG_ERROR("この実装は回転したRectのCollisionを支援しない。回転したRectも回転していなかったRectとみなす。");
		}
#endif

		// TouchかOverlapかを検出したいために、Rect::Overlap関数を使わない
		Vector2 lhsOpposite(lhsRect.OppositeX(), lhsRect.OppositeY());
		Vector2 rhsOpposite(rhsRect.OppositeX(), rhsRect.OppositeY());

		if (lhsRect.x >= rhsOpposite.x || lhsRect.y >= rhsOpposite.y ||
			rhsRect.x >= lhsOpposite.x || rhsRect.y >= lhsOpposite.y) {

			if (lhsRect.x == rhsOpposite.x || lhsRect.y == rhsOpposite.y ||
				rhsRect.x == lhsOpposite.x || rhsRect.y == lhsOpposite.y) {
				return CollidedType::Touch;
			} else {
				return CollidedType::None;
			}
		}

		return CollidedType::Overlap;
	}
}