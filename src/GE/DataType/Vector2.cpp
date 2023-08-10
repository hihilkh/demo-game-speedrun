#include "Vector2.h"
#include <cassert>
#include "GE/Utils/Math.h"

namespace GE::DataType::Internal
{
#pragma region TVector2の定義

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
	T TVector2<T>::operator[](std::size_t i) const
	{
		assert(i < TVector2::vectorSize && "Vector2 : IndexOutOfBounds");
		return *(&x + i);
	}

	template<VectorBaseType T>
	T& TVector2<T>::operator[](std::size_t i)
	{
		assert(i < TVector2::vectorSize && "Vector2 : IndexOutOfBounds");
		return *(&x + i);
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
		return std::sqrtf(SqrMagnitude());
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
			(float)std::lerp(a.x, b.x, t),
			(float)std::lerp(a.y, b.y, t)
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
	float TVector2<T>::AngleFromXAxis() const
	{
		float magnitude = this->Magnitude();
		if (magnitude == 0) {
			return 0;
		}

		float cosAngle = (float)Dot(*this, TVector2::right) / magnitude;
		float angle = Math::ToAngle(std::acos(cosAngle));
		if (this->y < 0) {
			angle = -angle;
		}
		return angle;
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

#pragma endregion

#pragma region Explicit Instantiation Definition

	template struct TVector2<int>;
	template struct TVector2<float>;

#pragma endregion
}