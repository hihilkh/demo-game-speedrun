﻿#pragma once

#include <cmath>
#include <type_traits>
#include <numbers>
#include <algorithm>

namespace GE::Math
{
	/// <summary>
	/// c++の負数の割り算は0への丸め(rounding toward zero)で、 -1 / 2 = 0　になる<para />
	/// -1 / 2 = -1 をしたい場合、この関数を使う
	/// </summary>
	inline int FloorDivide(int dividend, int divisor)
	{
		return (int)std::floor(float(dividend) / divisor);
	}

	inline constexpr float Clamp01(float num)
	{
		return std::clamp(num, 0.0f, 1.0f);
	}

	/// <summary>
	/// tを[0,1]にClampする
	/// </summary>
	inline constexpr float BoundedLerp(float a, float b, float t)
	{
		return std::lerp(a, b, Clamp01(t));
	}

	/// <returns>
	/// <para>正数 -> 1</para>
	/// <para>負数 -> -1</para>
	/// <para>0 -> 0</para>
	/// </returns>
	template <typename T>
	inline constexpr int Sign(T value)
	{
		return (value > T(0)) - (value < T(0));
	}

	/// <returns>
	/// <para>正数または0 -> 1</para>
	/// <para>負数 -> -1</para>
	/// </returns>
	template <typename T>
	inline constexpr int SignNonZero(T value)
	{
		return (value >= T(0)) - (value < T(0));
	}

	// TODO : rand()より良い方法を使う
#pragma region GetRandom

	/// <param name="min">含む</param>
	/// <param name="max">含まない</param>
	/// <returns>
	/// <para>min > max の場合, 戻り値は GetRandom(max, min) になる</para>
	/// min == max の場合, 戻り値は min になる
	/// </returns>
	template<typename T>
		requires std::is_integral_v<T>
	T GetRandom(T min, T max)
	{
		if (min > max) {
			return GetRandom(max, min);
		}
		else if (min == max) {
			return min;
		}

		return std::rand() % (max - min) + min;
	}

	/// <param name="min">含む</param>
	/// <param name="max">含む</param>
	/// <returns>
	/// <para>min > max の場合, 戻り値は GetRandom(max, min) になる</para>
	/// min == max の場合, 戻り値は min になる
	/// </returns>
	template<typename T>
		requires std::is_floating_point_v<T>
	T GetRandom(T min, T max)
	{
		if (min > max) {
			return GetRandom(max, min);
		}
		else if (min == max) {
			return min;
		}

		return (T)std::rand() / RAND_MAX * (max - min) + min;
	}

#pragma endregion

#pragma region Radian

	inline constexpr float ToRadian(float angle)
	{
		return angle * (float)std::numbers::pi / 180.0f;
	}

	inline constexpr float ToAngle(float radian)
	{
		return radian * 180.0f / (float)std::numbers::pi;
	}

#pragma endregion

}