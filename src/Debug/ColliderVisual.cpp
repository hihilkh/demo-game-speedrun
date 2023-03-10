#include "ColliderVisual.h"

#if defined(_DEBUG) && defined(DEBUG_COLLIDER)

#include <GameEngine_Ver3_83.h>
#include "Task/ResourceConstant.h"

namespace Debug::ColliderVisual
{
	namespace
	{
		DG::Image::SP WhiteImg;
		const ML::Box2D Src = ML::Box2D(0, 0, 32, 32);
		const ML::Color Color = ML::Color(0.5f, 1.0f, 0.0f, 0.0f);
	}

	void Render(const ML::Box2D& draw)
	{
		if (!WhiteImg) {
			WhiteImg = DG::Image::Create(ResourceConstant::ImageFolder + ResourceConstant::WhiteImage);
		}
		WhiteImg->Draw(draw, Src, Color);
	}
}

#endif