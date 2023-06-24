#pragma once

#include "GE/Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

namespace GE::Physics
{
	class RectCollider;
}

namespace GE::Debug::Physics
{
	void AddRectColliderVisual(const GE::Physics::RectCollider& collider);
}

#endif