#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Vector3.h"

namespace GE::DataType::Internal
{
#pragma region 宣言

	// 暗黙的な変換のための前方宣言
	template<typename T> struct TVector3;

	template<typename T>
	struct TVector2
	{
		static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "The type must be int or float");

		using FloatType = std::conditional_t<std::is_floating_point_v<T>, T, float>;
		using VectorFloatType = TVector2<FloatType>;

		T x, y;

		TVector2();
		TVector2(T x, T y);

		TVector2& operator+=(const TVector2& other);
		TVector2& operator-=(const TVector2& other);
		TVector2& operator*=(T multiple);
		TVector2& operator/=(T divisor);

		TVector2 operator-() const;

		TVector2& Scale(T multipleX, T multipleY);
		TVector2& Scale(const TVector2& other);
		static TVector2 Scale(const TVector2& lhs, const TVector2& rhs);

		static T Dot(const TVector2& lhs, const TVector2& rhs);

		FloatType Magnitude() const;
		T SqrMagnitude() const;
		static FloatType Distance(const TVector2& lhs, const TVector2& rhs);

		static VectorFloatType Lerp(const TVector2& a, const TVector2& b, float t);

		TVector2& Normalize();
		bool IsNormalized() const;

		// 暗黙的な変換

		operator TVector2<float>() const;
		operator TVector2<int>() const;
		operator TVector3<float>() const;
		operator TVector3<int>() const;

		// 定数

		static const TVector2 zero;
		static const TVector2 one;
		static const TVector2 up;
		static const TVector2 down;
		static const TVector2 left;
		static const TVector2 right;
	};

	template<typename T> TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<typename T> TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<typename T> TVector2<T> operator*(const TVector2<T>& vector, T multiple);
	template<typename T> TVector2<T> operator*(T multiple, const TVector2<T>& vector);
	template<typename T> TVector2<T> operator/(const TVector2<T>& vector, T divisor);
	template<typename T> bool operator==(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<typename T> bool operator!=(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<typename T> std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector);

#pragma endregion

#pragma region 定数定義

#define VECTOR2 template<> inline const TVector2<float> TVector2<float>

	VECTOR2::zero		(0.0f, 0.0f);
	VECTOR2::one		(1.0f, 1.0f);
	VECTOR2::up			(0.0f, 1.0f);
	VECTOR2::down		(0.0f, -1.0f);
	VECTOR2::left		(-1.0f, 0.0f);
	VECTOR2::right		(1.0f, 0.0f);

#undef VECTOR2

#define VECTOR2_INT template<> inline const TVector2<int> TVector2<int>

	VECTOR2_INT::zero	(0, 0);
	VECTOR2_INT::one	(1, 1);
	VECTOR2_INT::up		(0, 1);
	VECTOR2_INT::down	(0, -1);
	VECTOR2_INT::left	(-1, 0);
	VECTOR2_INT::right	(1, 0);

#undef VECTOR2_INT

#pragma endregion

#pragma region 関数定義

	template<typename T>
	inline TVector2<T>::TVector2() : TVector2<T>(T(), T())
	{
	}

	template<typename T>
	inline TVector2<T>::TVector2(T x, T y) : x(x), y(y)
	{
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::operator+=(const TVector2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::operator-=(const TVector2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::operator*=(T multiple)
	{
		return Scale(multiple, multiple);
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::operator/=(T divisor)
	{
		if constexpr (std::is_integral_v<T>) {
			x /= divisor;
			y /= divisor;
		} else {
			T multiple = 1 / divisor;
			*this *= multiple;
		}

		return *this;
	}

	template<typename T>
	inline TVector2<T> TVector2<T>::operator-() const
	{
		return TVector2<T>(-x, -y);
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::Scale(T multipleX, T multipleY)
	{
		x *= multipleX;
		y *= multipleY;
		return *this;
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::Scale(const TVector2<T>& other)
	{
		return Scale(other.x, other.y);
	}

	template<typename T>
	inline TVector2<T> TVector2<T>::Scale(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result.Scale(rhs);	// Return Value Optimization (RVO)のために、直接的に "return result.Scale(rhs);" をしない
		return result;
	}

	template<typename T>
	inline T TVector2<T>::Dot(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return	lhs.x * rhs.x +
				lhs.y * rhs.y;
	}

	template<typename T>
	inline TVector2<T>::FloatType TVector2<T>::Magnitude() const
	{
		return sqrt(SqrMagnitude());
	}

	template<typename T>
	inline T TVector2<T>::SqrMagnitude() const
	{
		return Dot(*this, *this);
	}

	template<typename T>
	inline TVector2<T>::FloatType TVector2<T>::Distance(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return (lhs - rhs).Magnitude();
	}

	template<typename T>
	inline TVector2<T>::VectorFloatType TVector2<T>::Lerp(const TVector2<T>& a, const TVector2<T>& b, float t)
	{
		return TVector2<T>::VectorFloatType(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t)
		);
	}

	template<typename T>
	inline TVector2<T>& TVector2<T>::Normalize()
	{
		// TODO : 
		// 今TVector2<int>でもNormalize()関数を持っている(使う場合はコンパイルエラーが生じる)
		// もっと良い方法を考えましょう
		static_assert(std::is_floating_point_v<T>, "Only Vector with float values is allowed to use this function");

		*this /= Magnitude();
		return *this;
	}

	template<typename T>
	inline bool TVector2<T>::IsNormalized() const
	{
		return SqrMagnitude() == 1;
	}

	template<typename T>
	inline TVector2<T>::operator TVector2<float>() const
	{
		return TVector2<float>(x, y);
	}

	template<typename T>
	inline TVector2<T>::operator TVector2<int>() const
	{
		return TVector2<int>(x, y);
	}

	template<typename T>
	inline TVector2<T>::operator TVector3<float>() const
	{
		return TVector3<float>(x, y, 0.0f);
	}

	template<typename T>
	inline TVector2<T>::operator TVector3<int>() const
	{
		return TVector3<int>(x, y, 0);
	}

	template<typename T>
	inline TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result += rhs;
		return result;
	}

	template<typename T>
	inline TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result -= rhs;
		return result;
	}

	template<typename T>
	inline TVector2<T> operator*(const TVector2<T>& vector, T multiple)
	{
		auto result = vector;
		result *= multiple;
		return result;
	}

	template<typename T>
	inline TVector2<T> operator*(T multiple, const TVector2<T>& vector)
	{
		return vector * multiple;
	}

	template<typename T>
	inline TVector2<T> operator/(const TVector2<T>& vector, T divisor)
	{
		TVector2<T> result = vector;
		result /= divisor;
		return result;
	}

	template<typename T>
	inline bool operator==(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return	lhs.x == rhs.x &&
				lhs.y == rhs.y;
	}

	template<typename T>
	inline bool operator!=(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ")";
	}

#pragma endregion

}