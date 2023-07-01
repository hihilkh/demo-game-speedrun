#include "ColliderVisual.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#include "GE/Debug/Log.h"

#include "GE/Core/GameObject.h"
#include "GE/Collision/Collider.h"

#include "GE/Collision/RectCollider.h"
#include "RectColliderVisual.h"

namespace GE::Debug::Collision
{
	void AddColliderVisual(const GE::Collision::Collider& collider)
	{
		auto rectCollider = dynamic_cast<const GE::Collision::RectCollider*>(&collider);
		if (rectCollider) {
			AddRectColliderVisual(*rectCollider);
			return;
		}

		DEBUG_LOG_WARNING("ColliderVisualはまだ実装していない。GameObject : " << collider.gameObject.GetName());
	}
}

#endif