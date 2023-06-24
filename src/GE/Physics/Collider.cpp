#include "Collider.h"
#include "GE/Core/GameObject.h"
#include "CollisionSystem.h"
#include "GE/Debug/Physics/ColliderVisual.h"

namespace GE::Physics
{
	Collider::Collider(GameObject& gameObject, bool isTrigger) :
		Component(gameObject),
		onCollided(),
		onTriggered(),
		isTrigger(isTrigger)
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
}