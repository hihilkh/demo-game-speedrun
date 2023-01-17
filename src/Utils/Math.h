﻿#pragma once

#include <cmath>

namespace Math
{
	/// <summary>
	/// c++の負数の割り算は0への丸め(rounding toward zero)で、 -1 / 2 = 0　になる<para />
	/// -1 / 2 = -1 をしたい場合、この関数を使う
	/// </summary>
	inline int FloorDivide(int dividend, int divisor)
	{
		return (int)floor(float(dividend) / divisor);
	}

	constexpr inline float Clamp01(float num)
	{
		return std::clamp(num, 0.0f, 1.0f);
	}

	/// <summary>
	/// tを[0,1]になる
	/// </summary>
	constexpr inline float BoundedLerp(float a, float b, float t)
	{
		return std::lerp(a, b, Clamp01(t));
	}
}