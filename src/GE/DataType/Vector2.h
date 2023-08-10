#pragma once

#include <iostream>
#include <type_traits>
#include "Vector3.h"
#include "GE/Utils/GEConcept.h"

namespace GE::DataType::Internal
{
#pragma region TVector2の宣言

	// 暗黙的な変換のための前方宣言
	template<VectorBaseType T>
	struct TVector3;

	template<VectorBaseType T>
	struct TVector2
	{
		static constexpr std::size_t vectorSize = 2;

		T x, y;

		TVector2();
		TVector2(T x, T y);

		TVector2& operator+=(const TVector2& other);
		TVector2& operator-=(const TVector2& other);
		TVector2& operator*=(T multiple);
		TVector2& operator/=(T divisor);

		TVector2 operator-() const;

		T operator[](std::size_t i) const;
		T& operator[](std::size_t i);

		TVector2& Scale(T multipleX, T multipleY);
		TVector2& Scale(const TVector2& other);
		static TVector2 Scale(const TVector2& lhs, const TVector2& rhs);

		static T Dot(const TVector2& lhs, const TVector2& rhs);

		float Magnitude() const;
		T SqrMagnitude() const;
		static float Distance(const TVector2& lhs, const TVector2& rhs);

		static TVector2<float> Lerp(const TVector2& a, const TVector2& b, float t);

		TVector2& Normalize() requires std::is_same_v<float, T>;

		TVector2& Rotate(float degree) requires std::is_same_v<float, T>;

		/// <summary>
		/// x軸(1, 0)からのなす角。
		/// </summary>
		/// <returns>
		/// <para>(-180, 180]</para>
		/// <para>特殊状況(例えば、zero vector)：0</para>
		/// </returns>
		float AngleFromXAxis() const;

		// 暗黙的な変換

		operator TVector2<float>() const requires (!std::is_same_v<float, T>);
		operator TVector2<int>() const requires (!std::is_same_v<int, T>);
		operator TVector3<float>() const requires (!std::is_same_v<float, T>);
		operator TVector3<int>() const requires (!std::is_same_v<int, T>);

		// 定数

		static const TVector2 zero;
		static const TVector2 one;
		static const TVector2 up;
		static const TVector2 down;
		static const TVector2 left;
		static const TVector2 right;
	};

#pragma endregion

#pragma region 定数定義

#define VECTOR2 template<> inline const TVector2<float> TVector2<float>

	VECTOR2::zero(0.0f, 0.0f);
	VECTOR2::one(1.0f, 1.0f);
	VECTOR2::up(0.0f, 1.0f);
	VECTOR2::down(0.0f, -1.0f);
	VECTOR2::left(-1.0f, 0.0f);
	VECTOR2::right(1.0f, 0.0f);

#undef VECTOR2

#define VECTOR2_INT template<> inline const TVector2<int> TVector2<int>

	VECTOR2_INT::zero(0, 0);
	VECTOR2_INT::one(1, 1);
	VECTOR2_INT::up(0, 1);
	VECTOR2_INT::down(0, -1);
	VECTOR2_INT::left(-1, 0);
	VECTOR2_INT::right(1, 0);

#undef VECTOR2_INT

#pragma endregion

#pragma region operator オーバーロード

#pragma region 宣言

	template<VectorBaseType T> TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> TVector2<T> operator*(const TVector2<T>& vector, T multiple);
	template<VectorBaseType T> TVector2<T> operator*(T multiple, const TVector2<T>& vector);
	template<VectorBaseType T> TVector2<T> operator/(const TVector2<T>& vector, T divisor);
	template<VectorBaseType T> bool operator==(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> bool operator!=(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector);

#pragma endregion

#pragma region 定義

	template<VectorBaseType T>
	TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result += rhs;
		return result;
	}

	template<VectorBaseType T>
	TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result -= rhs;
		return result;
	}

	template<VectorBaseType T>
	TVector2<T> operator*(const TVector2<T>& vector, T multiple)
	{
		auto result = vector;
		result *= multiple;
		return result;
	}

	template<VectorBaseType T>
	TVector2<T> operator*(T multiple, const TVector2<T>& vector)
	{
		return vector * multiple;
	}

	template<VectorBaseType T>
	TVector2<T> operator/(const TVector2<T>& vector, T divisor)
	{
		TVector2<T> result = vector;
		result /= divisor;
		return result;
	}

	template<VectorBaseType T>
	bool operator==(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return	lhs.x == rhs.x &&
				lhs.y == rhs.y;
	}

	template<VectorBaseType T>
	bool operator!=(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<VectorBaseType T>
	std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ")";
	}

#pragma endregion

#pragma endregion

#pragma region Explicit Instantiation Declaration

	extern template struct TVector2<int>;
	extern template struct TVector2<float>;

#pragma endregion
}