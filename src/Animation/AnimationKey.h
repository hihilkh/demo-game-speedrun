#pragma once

#include <myLib.h>
#include "Utils/Log.h"

namespace Animation
{
	struct AnimationKey {
		ML::Box2D imageSrc;
		int lastFrame;

		AnimationKey(int x, int y, int w, int h, int lastFrame) : imageSrc(ML::Box2D(x, y, w, h)), lastFrame(lastFrame) {
		}
	};
}
