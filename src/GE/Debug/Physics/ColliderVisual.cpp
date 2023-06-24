#include "ColliderVisual.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#include "GE/Debug/Log.h"

#include "GE/Core/GameObject.h"
#include "GE/Physics/Collider.h"

#include "GE/Physics/RectCollider.h"
#include "RectColliderVisual.h"

namespace GE::Debug::Physics
{
	void AddColliderVisual(const GE::Physics::Collider& collider)
	{
		auto rectCollider = dynamic_cast<const GE::Physics::RectCollider*>(&collider);
		if (rectCollider) {
			AddRectColliderVisual(*rectCollider);
			return;
		}

		DEBUG_LOG_WARNING("ColliderVisualはまだ実装していない。GameObject : " << collider.gameObject.GetName());
	}
}

#endif