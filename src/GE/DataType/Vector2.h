#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Vector3.h"
#include "GE/Utils/Math.h"
#include "GE/Utils/GEConcept.h"

namespace GE::DataType::Internal
{
#pragma region 宣言

	// 暗黙的な変換のための前方宣言
	template<VectorBaseType T>
	struct TVector3;

	template<VectorBaseType T>
	struct TVector2
	{
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

		float Magnitude() const;
		T SqrMagnitude() const;
		static float Distance(const TVector2& lhs, const TVector2& rhs);

		static TVector2<float> Lerp(const TVector2& a, const TVector2& b, float t);

		TVector2& Normalize() requires std::is_same_v<float, T>;

		TVector2& Rotate(float degree) requires std::is_same_v<float, T>;

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

	template<VectorBaseType T> TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> TVector2<T> operator*(const TVector2<T>& vector, T multiple);
	template<VectorBaseType T> TVector2<T> operator*(T multiple, const TVector2<T>& vector);
	template<VectorBaseType T> TVector2<T> operator/(const TVector2<T>& vector, T divisor);
	template<VectorBaseType T> bool operator==(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> bool operator!=(const TVector2<T>& lhs, const TVector2<T>& rhs);
	template<VectorBaseType T> std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector);

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

	template<VectorBaseType T>
	TVector2<T>::TVector2() : TVector2<T>(T(), T())
	{
	}

	template<VectorBaseType T>
	TVector2<T>::TVector2(T x, T y) : x(x), y(y)
	{
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::operator+=(const TVector2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::operator-=(const TVector2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::operator*=(T multiple)
	{
		return Scale(multiple, multiple);
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::operator/=(T divisor)
	{
		if constexpr (std::is_same_v<int, T>) {
			x /= divisor;
			y /= divisor;
		} else {
			T multiple = 1 / divisor;
			*this *= multiple;
		}

		return *this;
	}

	template<VectorBaseType T>
	TVector2<T> TVector2<T>::operator-() const
	{
		return TVector2<T>(-x, -y);
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::Scale(T multipleX, T multipleY)
	{
		x *= multipleX;
		y *= multipleY;
		return *this;
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::Scale(const TVector2<T>& other)
	{
		return Scale(other.x, other.y);
	}

	template<VectorBaseType T>
	TVector2<T> TVector2<T>::Scale(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		auto result = lhs;
		result.Scale(rhs);	// Return Value Optimization (RVO)のために、直接的に "return result.Scale(rhs);" をしない
		return result;
	}

	template<VectorBaseType T>
	T TVector2<T>::Dot(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return	lhs.x * rhs.x +
				lhs.y * rhs.y;
	}

	template<VectorBaseType T>
	float TVector2<T>::Magnitude() const
	{
		return sqrt(SqrMagnitude());
	}

	template<VectorBaseType T>
	T TVector2<T>::SqrMagnitude() const
	{
		return Dot(*this, *this);
	}

	template<VectorBaseType T>
	float TVector2<T>::Distance(const TVector2<T>& lhs, const TVector2<T>& rhs)
	{
		return (lhs - rhs).Magnitude();
	}

	template<VectorBaseType T>
	TVector2<float> TVector2<T>::Lerp(const TVector2<T>& a, const TVector2<T>& b, float t)
	{
		return TVector2<float>(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t)
		);
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::Normalize() requires std::is_same_v<float, T>
	{
		if (*this != TVector2::zero) {
			*this /= Magnitude();
		}

		return *this;
	}

	template<VectorBaseType T>
	TVector2<T>& TVector2<T>::Rotate(float degree) requires std::is_same_v<float, T>
	{
		float radian = Math::ToRadian(degree);
		float sinValue = std::sin(radian);
		float cosValue = std::cos(radian);

		T tempX = x;
		x = x * cosValue - y * sinValue;
		y = tempX * sinValue + y * cosValue;

		return *this;
	}

	template<VectorBaseType T>
	TVector2<T>::operator TVector2<float>() const requires (!std::is_same_v<float, T>)
	{
		return TVector2<float>((float)x, (float)y);
	}

	template<VectorBaseType T>
	TVector2<T>::operator TVector2<int>() const requires (!std::is_same_v<int, T>)
	{
		return TVector2<int>((int)x, (int)y);
	}

	template<VectorBaseType T>
	TVector2<T>::operator TVector3<float>() const requires (!std::is_same_v<float, T>)
	{
		return TVector3<float>((float)x, (float)y, 0.0f);
	}

	template<VectorBaseType T>
	TVector2<T>::operator TVector3<int>() const requires (!std::is_same_v<int, T>)
	{
		return TVector3<int>((int)x, (int)y, 0);
	}

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

}