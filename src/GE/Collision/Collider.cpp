#include "Collider.h"
#include "GE/Core/GameObject.h"
#include "CollisionSystem.h"
#include "GE/Debug/Collision/ColliderVisual.h"
#include "Detection/Detector.h"
#include "GE/Core/Transform2D.h"

namespace GE::Collision
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

	Detection::CollidedType Collider::CheckCollision(Collider& other)
	{
		return other.AcceptCollisionChecking(GetSelfDetector());
	}
}