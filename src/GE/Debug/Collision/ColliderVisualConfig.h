#pragma once

#include <cstdint>
#include "GE/DataType/Color.h"

namespace GE::Debug::Collision
{
	inline const int16_t colliderVisualRenderPriority = INT16_MAX;
	inline const GE::Color colliderColor = GE::Color(1.0f, 0.0f, 0.0f, 0.5f);	// 赤
	inline const GE::Color triggerColor = GE::Color(0.0f, 1.0f, 0.0f, 0.5f);	// 緑
}