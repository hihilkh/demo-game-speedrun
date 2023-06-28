#include "GE/Physics/RectCollider.h"
#include "GE/Core/Transform2D.h"
#include "GE/Debug/Log.h"
#include "GE/Core/GameObject.h"
#include "CollisionAdjustmentInfo.h"

namespace GE::Physics::CollisionDetection::SimpleImpl
{
#pragma region CheckCollision

	CollidedType CheckCollision(const RectCollider& lhs, const RectCollider& rhs)
	{
		Transform2DData lhsTransformData = lhs.GetTransform().GetWorldTransformData();
		Transform2DData rhsTransformData = rhs.GetTransform().GetWorldTransformData();

		Rect lhsRect = lhs.GetRect();
		Rect rhsRect = rhs.GetRect();

		return CheckCollision(
			lhsRect.Move(lhsTransformData.pos),
			lhsTransformData.rot,
			rhsRect.Move(rhsTransformData.pos),
			rhsTransformData.rot);
	}

	CollidedType CheckCollision(const Rect& lhsRect, float lhsRot, const Rect& rhsRect, float rhsRot)
	{
		if (lhsRot == 0 && rhsRot == 0) {
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

		DEBUG_LOG_ERROR("回転したRectのDetermineOverlappingはまだ実装していない。");
		return CollidedType::None;
	}

#pragma endregion

#pragma region RecordCollisionAdjustment

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

		float GetBoundPos(const Rect& targetRect, const Rect& oppositeRect, AdjustDir dir)
		{
			switch (dir) {
				case AdjustDir::Left:	return oppositeRect.x - targetRect.x - targetRect.width;
				case AdjustDir::Right:	return oppositeRect.x + oppositeRect.width - targetRect.x;
				case AdjustDir::Up:		return oppositeRect.y + oppositeRect.height - targetRect.y;
				case AdjustDir::Down:	return oppositeRect.y - targetRect.y - targetRect.height;

			}

			// 警告を出さないように
			return 0.0f;
		}
	}

	void RecordCollisionAdjustment(RectCollider& lhs, RectCollider& rhs)
	{
		if (lhs.gameObject.GetIsStatic() && rhs.gameObject.GetIsStatic()) {
			return;
		}

		Transform2DData lhsTransformData = lhs.GetTransform().GetWorldTransformData();
		Transform2DData rhsTransformData = rhs.GetTransform().GetWorldTransformData();

		Rect lhsRect = lhs.GetRect();
		lhsRect.Move(lhsTransformData.pos);
		Rect rhsRect = rhs.GetRect();
		rhsRect.Move(rhsTransformData.pos);

		if (lhsTransformData.rot == 0 && rhsTransformData.rot == 0) {
			Vector2 vectorFromTwoCenter = rhsRect.Center() - lhsRect.Center();

			AdjustDir rhsAdjustDirX = vectorFromTwoCenter.x > 0 ? AdjustDir::Right : AdjustDir::Left;
			AdjustDir rhsAdjustDirY = vectorFromTwoCenter.y > 0 ? AdjustDir::Up : AdjustDir::Down;

			if (lhs.gameObject.GetIsStatic()) {
				float boundPosX = GetBoundPos(rhsRect, lhsRect, rhsAdjustDirX);
				float boundPosY = GetBoundPos(rhsRect, lhsRect, rhsAdjustDirY);

				rhs.AddAdjustmentInfo(boundPosX, boundPosY);
			} else if (rhs.gameObject.GetIsStatic()) {
				float boundPosX = GetBoundPos(lhsRect, rhsRect, OppositeDir(rhsAdjustDirX));
				float boundPosY = GetBoundPos(lhsRect, rhsRect, OppositeDir(rhsAdjustDirY));

				lhs.AddAdjustmentInfo(boundPosX, boundPosY);
			} else {
				float boundPosX = GetBoundPos(rhsRect, lhsRect, rhsAdjustDirX) / 2.0f;
				float boundPosY = GetBoundPos(rhsRect, lhsRect, rhsAdjustDirY) / 2.0f;

				lhs.AddAdjustmentInfo(-boundPosX, -boundPosY);
				rhs.AddAdjustmentInfo(boundPosX, boundPosY);
			}

			return;
		}

		DEBUG_LOG_ERROR("回転したRectのAdjustPosはまだ実装していない。");
		return;
	}

#pragma endregion
}