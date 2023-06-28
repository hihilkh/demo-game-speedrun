#pragma once

#include <cstdint>

namespace GE::Physics::CollisionLayer
{
	using Bitmask = std::uint32_t;

	inline const Bitmask general = 1 << 0;

	inline const Bitmask none = 0;
	inline const Bitmask all = UINT32_MAX;
}