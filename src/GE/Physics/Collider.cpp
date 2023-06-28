#include "Collider.h"
#include "GE/Core/GameObject.h"
#include "CollisionSystem.h"
#include "GE/Debug/Physics/ColliderVisual.h"
#include "CollisionDetection/Detector.h"
#include "GE/Core/Transform2D.h"

namespace GE::Physics
{
	Collider::Collider(GameObject& gameObject, bool isTrigger) :
		Component(gameObject),
		onCollided(),
		onTriggered(),
		isTrigger(isTrigger),
		layer(CollisionLayer::general)
	{
	}

	void Collider::Start()
	{
		CollisionSystem::AddCollider(*this);

		ADD_COLLIDER_VISUAL(*this);
	}

	void Collider::PreDestroy()
	{
		CollisionSystem::RemoveCollider(*this);
	}

	CollisionDetection::CollidedType Collider::CheckCollision(const Collider& other) const
	{
		return other.AcceptCollisionChecking(GetSelfDetector());
	}

	void Collider::RecordCollisionAdjustment(Collider& other)
	{
		return other.AcceptCollisionAdjustmentRecord(GetSelfDetector());
	}
}