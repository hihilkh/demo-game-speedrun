﻿#pragma once

#include <iostream>
#include <type_traits>
#include "Vector2.h"
#include "GE/Utils/GEConcept.h"

namespace GE::DataType::Internal
{
#pragma region TVector3の宣言

	// 暗黙的な変換のための前方宣言
	template<VectorBaseType T> struct TVector2;

	template<VectorBaseType T>
	struct TVector3
	{
		static constexpr std::size_t vectorSize = 3;

		T x, y, z;

		TVector3();
		TVector3(T x, T y, T z);

		TVector3& operator+=(const TVector3& other);
		TVector3& operator-=(const TVector3& other);
		TVector3& operator*=(T multiple);
		TVector3& operator/=(T divisor);

		TVector3 operator-() const;

		T operator[](std::size_t i) const;
		T& operator[](std::size_t i);

		TVector3& Scale(T multipleX, T multipleY, T multipleZ);
		TVector3& Scale(const TVector3& other);
		static TVector3 Scale(const TVector3& lhs, const TVector3& rhs);

		static T Dot(const TVector3& lhs, const TVector3& rhs);
		static TVector3 Cross(const TVector3& lhs, const TVector3& rhs);

		float Magnitude() const;
		T SqrMagnitude() const;
		static float Distance(const TVector3& lhs, const TVector3& rhs);

		static TVector3<float> Lerp(const TVector3& a, const TVector3& b, float t);

		TVector3& Normalize() requires std::is_same_v<float, T>;

		// TODO : Rotate関数
		
		// 暗黙的な変換

		operator TVector2<float>() const requires (!std::is_same_v<float, T>);
		operator TVector2<int>() const requires (!std::is_same_v<int, T>);
		operator TVector3<float>() const requires (!std::is_same_v<float, T>);
		operator TVector3<int>() const requires (!std::is_same_v<int, T>);

		// 定数

		static const TVector3 zero;
		static const TVector3 one;
		static const TVector3 up;
		static const TVector3 down;
		static const TVector3 left;
		static const TVector3 right;
		static const TVector3 forward;
		static const TVector3 backward;
	};

#pragma endregion

#pragma region 定数定義

#define VECTOR3 template<> inline const TVector3<float> TVector3<float>

	VECTOR3::zero			(0.0f, 0.0f, 0.0f);
	VECTOR3::one			(1.0f, 1.0f, 1.0f);
	VECTOR3::up				(0.0f, 1.0f, 0.0f);
	VECTOR3::down			(0.0f, -1.0f, 0.0f);
	VECTOR3::left			(1.0f, 0.0f, 0.0f);
	VECTOR3::right			(-1.0f, 0.0f, 0.0f);
	VECTOR3::forward		(0.0f, 0.0f, 1.0f);
	VECTOR3::backward		(0.0f, 0.0f, -1.0f);

#undef VECTOR3

#define VECTOR3_INT template<> inline const TVector3<int> TVector3<int>

	VECTOR3_INT::zero		(0, 0, 0);
	VECTOR3_INT::one		(1, 1, 1);
	VECTOR3_INT::up			(0, 1, 0);
	VECTOR3_INT::down		(0, -1, 0);
	VECTOR3_INT::left		(1, 0, 0);
	VECTOR3_INT::right		(-1, 0, 0);
	VECTOR3_INT::forward	(0, 0, 1);
	VECTOR3_INT::backward	(0, 0, -1);

#undef VECTOR3_INT

#pragma endregion

#pragma region operator オーバーロード

#pragma region 宣言

	template<VectorBaseType T> TVector3<T> operator+(const TVector3<T>& lhs, const TVector3<T>& rhs);
	template<VectorBaseType T> TVector3<T> operator-(const TVector3<T>& lhs, const TVector3<T>& rhs);
	template<VectorBaseType T> TVector3<T> operator*(const TVector3<T>& vector, T multiple);
	template<VectorBaseType T> TVector3<T> operator*(T multiple, const TVector3<T>& vector);
	template<VectorBaseType T> TVector3<T> operator/(const TVector3<T>& vector, T divisor);
	template<VectorBaseType T> bool operator==(const TVector3<T>& lhs, const TVector3<T>& rhs);
	template<VectorBaseType T> bool operator!=(const TVector3<T>& lhs, const TVector3<T>& rhs);
	template<VectorBaseType T> std::ostream& operator<<(std::ostream& os, const TVector3<T>& vector);

#pragma endregion

#pragma region 定義

	template<VectorBaseType T>
	TVector3<T> operator+(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		auto result = lhs;
		result += rhs;
		return result;
	}

	template<VectorBaseType T>
	TVector3<T> operator-(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		auto result = lhs;
		result -= rhs;
		return result;
	}

	template<VectorBaseType T>
	TVector3<T> operator*(const TVector3<T>& vector, T multiple)
	{
		auto result = vector;
		result *= multiple;
		return result;
	}

	template<VectorBaseType T>
	TVector3<T> operator*(T multiple, const TVector3<T>& vector)
	{
		return vector * multiple;
	}

	template<VectorBaseType T>
	TVector3<T> operator/(const TVector3<T>& vector, T divisor)
	{
		auto result = vector;
		result /= divisor;
		return result;
	}

	template<VectorBaseType T>
	bool operator==(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		return	lhs.x == rhs.x &&
				lhs.y == rhs.y &&
				lhs.z == rhs.z;
	}

	template<VectorBaseType T>
	bool operator!=(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<VectorBaseType T>
	std::ostream& operator<<(std::ostream& os, const TVector3<T>& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	}

#pragma endregion

#pragma endregion

#pragma region Explicit Instantiation Declaration

	extern template struct TVector3<int>;
	extern template struct TVector3<float>;

#pragma endregion

}