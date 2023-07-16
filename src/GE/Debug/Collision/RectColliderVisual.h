#pragma once

#include "GE/Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#include "GE/Utils/TypeDef.h"

namespace GE::Debug::Collision
{
	void AddRectColliderVisual(const RectCollider& collider);
}

#endif