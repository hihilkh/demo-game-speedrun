#include "Vector3.h"
#include <cassert>
#include <cmath>

namespace GE::DataType::Internal
{
#pragma region TVector3の定義

	template<VectorBaseType T>
	TVector3<T>::TVector3() : TVector3(T(), T(), T())
	{
	}

	template<VectorBaseType T>
	TVector3<T>::TVector3(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::operator+=(const TVector3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::operator-=(const TVector3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::operator*=(T multiple)
	{
		return Scale(multiple, multiple, multiple);
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::operator/=(T divisor)
	{
		if constexpr (std::is_same_v<int, T>) {
			x /= divisor;
			y /= divisor;
			z /= divisor;
		} else {
			T multiple = 1 / divisor;
			*this *= multiple;
		}

		return *this;
	}

	template<VectorBaseType T>
	TVector3<T> TVector3<T>::operator-() const
	{
		return TVector3<T>(-x, -y, -z);
	}

	template<VectorBaseType T>
	T TVector3<T>::operator[](std::size_t i) const
	{
		assert(i < TVector3::vectorSize && "Vector3 : IndexOutOfBounds");
		return *(&x + i);
	}

	template<VectorBaseType T>
	T& TVector3<T>::operator[](std::size_t i)
	{
		assert(i < TVector3::vectorSize && "Vector3 : IndexOutOfBounds");
		return *(&x + i);
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::Scale(T multipleX, T multipleY, T multipleZ)
	{
		x *= multipleX;
		y *= multipleY;
		z *= multipleZ;
		return *this;
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::Scale(const TVector3<T>& other)
	{
		return Scale(other.x, other.y, other.z);
	}

	template<VectorBaseType T>
	TVector3<T> TVector3<T>::Scale(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		auto result = lhs;
		result.Scale(rhs);	// Return Value Optimization (RVO)のために、直接的に "return result.Scale(rhs);" をしない
		return result;
	}


	template<VectorBaseType T>
	T TVector3<T>::Dot(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		return	lhs.x * rhs.x +
				lhs.y * rhs.y +
				lhs.z * rhs.z;
	}

	template<VectorBaseType T>
	TVector3<T> TVector3<T>::Cross(const TVector3<T>& lhs, const TVector3<T>& rhs)
	{
		return TVector3<T>(
			lhs.y * rhs.z - lhs.z * rhs.y,
			-lhs.x * rhs.z + lhs.z * rhs.x,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	template<VectorBaseType T>
	float TVector3<T>::Magnitude() const
	{
		return std::sqrtf(SqrMagnitude());
	}

	template<VectorBaseType T>
	T TVector3<T>::SqrMagnitude() const
	{
		return Dot(*this, *this);
	}

	template<VectorBaseType T>
	float TVector3<T>::Distance(const TVector3& lhs, const TVector3& rhs)
	{
		return (lhs - rhs).Magnitude();
	}

	template<VectorBaseType T>
	TVector3<float> TVector3<T>::Lerp(const TVector3<T>& a, const TVector3<T>& b, float t)
	{
		return TVector3<float>(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t),
			std::lerp(a.z, b.z, t)
		);
	}

	template<VectorBaseType T>
	TVector3<T>& TVector3<T>::Normalize() requires std::is_same_v<float, T>
	{
		if (*this != TVector3::zero) {
			*this /= Magnitude();
		}

		return *this;
	}

	template<VectorBaseType T>
	TVector3<T>::operator TVector2<float>() const requires (!std::is_same_v<float, T>)
	{
		return TVector2<float>((float)x, (float)y);
	}

	template<VectorBaseType T>
	TVector3<T>::operator TVector2<int>() const requires (!std::is_same_v<int, T>)
	{
		return TVector2<int>((int)x, (int)y);
	}

	template<VectorBaseType T>
	TVector3<T>::operator TVector3<float>() const requires (!std::is_same_v<float, T>)
	{
		return TVector3<float>((float)x, (float)y, (float)z);
	}

	template<VectorBaseType T>
	TVector3<T>::operator TVector3<int>() const requires (!std::is_same_v<int, T>)
	{
		return TVector3<int>((int)x, (int)y, (int)z);
	}

#pragma endregion

#pragma region Explicit Instantiation Definition

	template struct TVector3<int>;
	template struct TVector3<float>;

#pragma endregion
}