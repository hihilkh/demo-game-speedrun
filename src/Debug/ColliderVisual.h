#pragma once

#define DEBUG_COLLIDER

#ifdef DEBUG_COLLIDER

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