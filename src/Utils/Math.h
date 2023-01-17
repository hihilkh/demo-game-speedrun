#pragma once

#include <cmath>

// TODO : もしC++17 / 20になると、こっちの関数がまだ必要があるかどうかを見直す
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

	inline float Clamp01(float num)
	{
		return max(0.0f, min(1.0f, num));
	}

	inline float Lerp(float from, float to, float progress)
	{
		return from + (to - from) * Clamp01(progress);
	}

	static const double PI = 3.141592653589793;
}