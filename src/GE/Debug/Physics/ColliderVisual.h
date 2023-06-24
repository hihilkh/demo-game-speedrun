#pragma once

#include "GE/Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

namespace GE::Physics
{
	class Collider;
}

namespace GE::Debug::Physics
{
	void AddColliderVisual(const GE::Physics::Collider& collider);
}

#define ADD_COLLIDER_VISUAL(collider) GE::Debug::Physics::AddColliderVisual(collider)

#else

#define ADD_COLLIDER_VISUAL(draw)

#endif