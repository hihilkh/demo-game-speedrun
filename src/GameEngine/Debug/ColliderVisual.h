#pragma once

// TODO : コードスタンダードに合わせるように
#include "DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_COLLIDER_VISUAL)

#pragma region 前方宣言

namespace ML { class Box2D; }

#pragma endregion

namespace Debug::ColliderVisual
{
	void Render(const ML::Box2D& draw);
}

#define RenderColliderVisual(draw) Debug::ColliderVisual::Render(draw)

#else

#define RenderColliderVisual(draw)

#endif