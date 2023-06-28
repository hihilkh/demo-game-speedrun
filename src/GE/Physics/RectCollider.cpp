#include "RectCollider.h"
#include "CollisionDetection/Detector.h"
#include "GE/Core/Transform2D.h"

namespace GE::Physics
{
	RectCollider::RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect) :
		Collider(gameObject, isTrigger),
		rect(rect)
	{

	}

	CollisionDetection::CollidedType RectCollider::AcceptCollisionChecking(const CollisionDetection::Detector& detector) const
	{
		return detector.CheckCollision(*this);
	}

	void RectCollider::AcceptCollisionAdjustmentRecord(CollisionDetection::Detector& detector)
	{
		return detector.RecordCollisionAdjustment(*this);
	}

	void RectCollider::AdjustCollidedPos()
	{
		Vector2 posOffset = GetCollisionAdjustmentPosOffset();
		GetTransform().SetWorldPos(GetTransform().GetWorldPos() + posOffset);
	}
}