#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Vector2.h"

namespace GE
{
	namespace PrivateTemplate
	{
#pragma region 宣言

		// 暗黙的な変換のための前方宣言
		template<typename T> struct TVector2;

		template<typename T>
		struct TVector3
		{
			static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "The type must be int or float");

			typedef std::conditional_t<std::is_floating_point_v<T>, T, float> FloatType;
			typedef std::conditional_t<std::is_floating_point_v<T>, TVector3<T>, TVector3<float>> VectorFloatType;

			T x, y, z;

			TVector3();
			TVector3(T x, T y, T z);

			TVector3& operator+=(const TVector3& other);
			TVector3& operator-=(const TVector3& other);
			TVector3& operator*=(T multiple);
			TVector3& operator/=(T divisor);

			TVector3 operator-() const;

			TVector3& Scale(T multipleX, T multipleY, T multipleZ);
			TVector3& Scale(const TVector3& other);
			static TVector3 Scale(const TVector3& lhs, const TVector3& rhs);

			static T Dot(const TVector3& lhs, const TVector3& rhs);
			static TVector3 Cross(const TVector3& lhs, const TVector3& rhs);

			FloatType Magnitude() const;
			T SqrMagnitude() const;
			static FloatType Distance(const TVector3& lhs, const TVector3& rhs);

			static VectorFloatType Lerp(const TVector3& a, const TVector3& b, float t);

			TVector3& Normalize();
			bool IsNormalized() const;

			// 暗黙的な変換

			operator TVector2<float>() const;
			operator TVector2<int>() const;
			operator TVector3<float>() const;
			operator TVector3<int>() const;

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

		template<typename T> TVector3<T> operator+(const TVector3<T>& lhs, const TVector3<T>& rhs);
		template<typename T> TVector3<T> operator-(const TVector3<T>& lhs, const TVector3<T>& rhs);
		template<typename T> TVector3<T> operator*(const TVector3<T>& vector, T multiple);
		template<typename T> TVector3<T> operator*(T multiple, const TVector3<T>& vector);
		template<typename T> TVector3<T> operator/(const TVector3<T>& vector, T divisor);
		template<typename T> bool operator==(const TVector3<T>& lhs, const TVector3<T>& rhs);
		template<typename T> bool operator!=(const TVector3<T>& lhs, const TVector3<T>& rhs);
		template<typename T> std::ostream& operator<<(std::ostream& os, const TVector3<T>& vector);

#pragma endregion

#pragma region 定数定義

#define VECTOR3 template<> inline const TVector3<float> TVector3<float>

		VECTOR3::zero		( 0.0f,  0.0f,  0.0f);
		VECTOR3::one		( 1.0f,  1.0f,  1.0f);
		VECTOR3::up			( 0.0f,  1.0f,  0.0f);
		VECTOR3::down		( 0.0f, -1.0f,  0.0f);
		VECTOR3::left		( 1.0f,  0.0f,  0.0f);
		VECTOR3::right		(-1.0f,  0.0f,  0.0f);
		VECTOR3::forward	( 0.0f,  0.0f,  1.0f);
		VECTOR3::backward	( 0.0f,  0.0f, -1.0f);

#undef VECTOR3

#define VECTOR3_INT template<> inline const TVector3<int> TVector3<int>

		VECTOR3_INT::zero		( 0,  0,  0);
		VECTOR3_INT::one		( 1,  1,  1);
		VECTOR3_INT::up			( 0,  1,  0);
		VECTOR3_INT::down		( 0, -1,  0);
		VECTOR3_INT::left		( 1,  0,  0);
		VECTOR3_INT::right		(-1,  0,  0);
		VECTOR3_INT::forward	( 0,  0,  1);
		VECTOR3_INT::backward	( 0,  0, -1);

#undef VECTOR3_INT

#pragma endregion

#pragma region 関数定義

		template<typename T>
		inline TVector3<T>::TVector3() : TVector3(T(), T(), T())
		{
		}

		template<typename T>
		inline TVector3<T>::TVector3(T x, T y, T z) : x(x), y(y), z(z)
		{
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::operator+=(const TVector3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::operator-=(const TVector3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::operator*=(T multiple)
		{
			return Scale(multiple, multiple, multiple);
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::operator/=(T divisor)
		{
			if constexpr (std::is_integral_v<T>) {
				x /= divisor;
				y /= divisor;
				z /= divisor;
			} else {
				T multiple = 1 / divisor;
				*this *= multiple;
			}

			return *this;
		}

		template<typename T>
		inline TVector3<T> TVector3<T>::operator-() const
		{
			return TVector3<T>(-x, -y, -z);
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::Scale(T multipleX, T multipleY, T multipleZ)
		{
			x *= multipleX;
			y *= multipleY;
			z *= multipleZ;
			return *this;
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::Scale(const TVector3<T>& other)
		{
			return Scale(other.x, other.y, other.z);
		}

		template<typename T>
		inline TVector3<T> TVector3<T>::Scale(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			auto result = lhs;
			return result.Scale(rhs);
		}


		template<typename T>
		inline T TVector3<T>::Dot(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			return	lhs.x * rhs.x +
					lhs.y * rhs.y +
					lhs.z * rhs.z;
		}

		template<typename T>
		inline TVector3<T> TVector3<T>::Cross(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			return TVector3<T>(
				  lhs.y * rhs.z - lhs.z * rhs.y,
				- lhs.x * rhs.z + lhs.z * rhs.x,
				  lhs.x * rhs.y - lhs.y * rhs.x
			);
		}

		template<typename T>
		inline TVector3<T>::FloatType TVector3<T>::Magnitude() const
		{
			return sqrt(SqrMagnitude());
		}

		template<typename T>
		inline T TVector3<T>::SqrMagnitude() const
		{
			return Dot(*this, *this);
		}

		template<typename T>
		inline TVector3<T>::FloatType TVector3<T>::Distance(const TVector3& lhs, const TVector3& rhs)
		{
			return (lhs - rhs).Magnitude();
		}

		template<typename T>
		inline TVector3<T>::VectorFloatType TVector3<T>::Lerp(const TVector3<T>& a, const TVector3<T>& b, float t)
		{
			return TVector3<T>::VectorFloatType(
				std::lerp(a.x, b.x, t),
				std::lerp(a.y, b.y, t),
				std::lerp(a.z, b.z, t)
			);
		}

		template<typename T>
		inline TVector3<T>& TVector3<T>::Normalize()
		{
			// TODO : 
			// 今TVector3<int>でもNormalize()関数を持っている(使う場合はコンパイルエラーが生じる)
			// もっと良い方法を考えましょう
			static_assert(std::is_floating_point_v<T>, "Only Vector with float values is allowed to use this function");

			*this /= Magnitude();
			return *this;
		}

		template<typename T>
		inline bool TVector3<T>::IsNormalized() const
		{
			return SqrMagnitude() == 1;
		}

		template<typename T>
		inline TVector3<T>::operator TVector2<float>() const
		{
			return TVector2<float>(x, y);
		}

		template<typename T>
		inline TVector3<T>::operator TVector2<int>() const
		{
			return TVector2<int>(x, y);
		}

		template<typename T>
		inline TVector3<T>::operator TVector3<float>() const
		{
			return TVector3<float>(x, y, z);
		}

		template<typename T>
		inline TVector3<T>::operator TVector3<int>() const
		{
			return TVector3<int>(x, y, z);
		}

		template<typename T>
		inline TVector3<T> operator+(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			auto result = lhs;
			return result += rhs;
		}

		template<typename T>
		inline TVector3<T> operator-(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			auto result = lhs;
			return result -= rhs;
		}

		template<typename T>
		inline TVector3<T> operator*(const TVector3<T>& vector, T multiple)
		{
			auto result = vector;
			return result *= multiple;
		}

		template<typename T>
		inline TVector3<T> operator*(T multiple, const TVector3<T>& vector)
		{
			return vector * multiple;
		}

		template<typename T>
		inline TVector3<T> operator/(const TVector3<T>& vector, T divisor)
		{
			auto result = vector;
			return result /= divisor;
		}

		template<typename T>
		inline bool operator==(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			return	lhs.x == rhs.x &&
					lhs.y == rhs.y &&
					lhs.z == rhs.z;
		}

		template<typename T>
		inline bool operator!=(const TVector3<T>& lhs, const TVector3<T>& rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T>
		inline std::ostream& operator<<(std::ostream& os, const TVector3<T>& vector)
		{
			return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		}

#pragma endregion

	}

	typedef PrivateTemplate::TVector3<float>	Vector3;
	typedef PrivateTemplate::TVector3<int>		Vector3Int;
}