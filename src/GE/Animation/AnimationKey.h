#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include <cstdint>

namespace GE::Animation
{
	struct AnimationKey
	{
		enum class AnimationType : uint8_t
		{
			Constant = 0,
			Linear = 1,
		};

		AnimationType animType;
		RectPixel imgSrcRect;
	};
}