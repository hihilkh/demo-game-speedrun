#pragma once

#include "GE/Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

namespace GE::Collision
{
	class RectCollider;
}

namespace GE::Debug::Collision
{
	void AddRectColliderVisual(const GE::Collision::RectCollider& collider);
}

#endif