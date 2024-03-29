﻿#pragma once

#include <cstdint>

namespace GE::Render::RenderLayer
{
	using Bitmask = std::uint32_t;

	inline const Bitmask general = 1 << 0;
	inline const Bitmask ui = 1 << 1;

	inline const Bitmask none = 0;
	inline const Bitmask all = UINT32_MAX;
	inline const Bitmask nonUI = ~ui;
}
