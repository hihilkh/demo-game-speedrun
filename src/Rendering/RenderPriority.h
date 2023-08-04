#pragma once

#include <cstdint>

namespace RenderPriority
{
	inline const std::int16_t background	= 0;
	inline const std::int16_t mapBack		= 50;
	inline const std::int16_t mapObject		= 60;
	inline const std::int16_t enemy			= 100;
	inline const std::int16_t player		= 150;
	inline const std::int16_t mapFront		= 200;

	inline const std::int16_t overlay		= 1000;
}