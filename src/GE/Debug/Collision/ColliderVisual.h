#pragma once

#include "GE/Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

namespace GE::Collision
{
	class Collider;
}

namespace GE::Debug::Collision
{
	void AddColliderVisual(const GE::Collision::Collider& collider);
}

#define ADD_COLLIDER_VISUAL(collider) GE::Debug::Collision::AddColliderVisual(collider)

#else

#define ADD_COLLIDER_VISUAL(collider)

#endif