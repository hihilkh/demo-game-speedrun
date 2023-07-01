#pragma once

#include <cstdint>

namespace GE::Collision::Detection
{
	enum class CollidedType : std::uint8_t
	{
		None,
		Touch,
		Overlap,
	};
}