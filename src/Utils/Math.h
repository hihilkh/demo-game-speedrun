#pragma once

#include <cmath>
#include <type_traits>

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

	inline constexpr float Clamp01(float num)
	{
		return std::clamp(num, 0.0f, 1.0f);
	}

	/// <summary>
	/// tを[0,1]になる
	/// </summary>
	inline constexpr float BoundedLerp(float a, float b, float t)
	{
		return std::lerp(a, b, Clamp01(t));
	}

#pragma region GetRandom

	/// <param name="min">含む</param>
	/// <param name="max">含まない</param>
	/// <returns>
	/// <para>min > max の場合, 戻り値は GetRandom(max, min) になる</para>
	/// min == max の場合, 戻り値は min になる
	/// </returns>
	template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline T GetRandom(T min, T max)
	{
		if (min > max) {
			return GetRandom(max, min);
		}
		else if (min == max) {
			return min;
		}

		return rand() % (max - min) + min;
	}

	/// <param name="min">含む</param>
	/// <param name="max">含む</param>
	/// <returns>
	/// <para>min > max の場合, 戻り値は GetRandom(max, min) になる</para>
	/// min == max の場合, 戻り値は min になる
	/// </returns>
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	inline T GetRandom(T min, T max)
	{
		if (min > max) {
			return GetRandom(max, min);
		}
		else if (min == max) {
			return min;
		}

		return (T)rand() / RAND_MAX * (max - min) + min;
	}

#pragma endregion
}