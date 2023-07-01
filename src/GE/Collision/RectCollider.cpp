#include "RectCollider.h"
#include "Detection/Detector.h"
#include "GE/Core/Transform2D.h"

namespace GE::Collision
{
	RectCollider::RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect) :
		Collider(gameObject, isTrigger),
		rect(rect),
		detector(*this)
	{
	}

	Detection::CollidedType RectCollider::AcceptCollisionChecking(Detection::Detector& fromDetector)
	{
		return fromDetector.CheckCollision(*this, this->detector);
	}

	void RectCollider::AdjustCollidedPos()
	{
		Vector2 posOffset = detector.GetCollisionAdjustmentPosOffset();
		GetTransform().SetWorldPos(GetTransform().GetWorldPos() + posOffset);
	}
}