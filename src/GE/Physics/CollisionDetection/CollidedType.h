#pragma once

#include <cstdint>

namespace GE::Physics::CollisionDetection
{
	enum class CollidedType : std::uint8_t
	{
		None,
		Touch,
		Overlap,
	};
}