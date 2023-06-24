#pragma once

#include <cstdint>
#include <limits>
#include "GE/DataType/Color.h"

namespace GE::Debug::Physics
{
	inline const int16_t colliderVisualRenderPriority = std::numeric_limits<int16_t>::max();
	inline const GE::Color colliderColor = GE::Color(1.0f, 0.0f, 0.0f, 0.5f);	// 赤
	inline const GE::Color triggerColor = GE::Color(0.0f, 1.0f, 0.0f, 0.5f);	// 緑
}