#include "Rect.h"
#include "GE/Utils/Math.h"

namespace GE::DataType::Internal
{
#pragma region TRectの定義

	template<RectBaseType T>
	TRect<T>::TRect() : TRect(T(), T(), T(), T())
	{
	}

	template<RectBaseType T>
	TRect<T>::TRect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
	{
	}

	template<RectBaseType T>
	TRect<T>::TRect(const TVector2<T>& pos, const TVector2<T>& size) : pos(pos), size(size)
	{
	}

	template<RectBaseType T>
	TRect<T> TRect<T>::FromCenter(T width, T height)
	{
		return TRect(-(width / 2), -(height / 2), width, height);
	}

	template<RectBaseType T>
	TRect<T> TRect<T>::FromCenter(const TVector2<T>& size)
	{
		return FromCenter(size.x, size.y);
	}

	template<RectBaseType T>
	TRect<T> TRect<T>::FromDiagonal(T x, T y, T oppositeX, T oppositeY)
	{
		T deltaX = oppositeX - x;
		T deltaY = oppositeY - y;

		if constexpr (std::is_same_v<int, T>) {
			return TRect(x, y, deltaX + Math::SignNonZero(deltaX), deltaY + Math::SignNonZero(deltaY));
		} else {
			return TRect(x, y, deltaX, deltaY);
		}
	}

	template<RectBaseType T>
	TRect<T> TRect<T>::FromDiagonal(const TVector2<T>& point, const TVector2<T>& oppositePoint)
	{
		return FromDiagonal(point.x, point.y, oppositePoint.x, oppositePoint.y);
	}

	template<RectBaseType T>
	T TRect<T>::Area() const
	{
		return width * height;
	}

	template<RectBaseType T>
	TVector2<T> TRect<T>::Center() const
	{
		return pos + size / T(2);
	}

	template<RectBaseType T>
	bool TRect<T>::IsEmpty() const
	{
		if constexpr (std::is_same_v<int, T>) {
			return width == 0 || height == 0;
		} else {
			return false;
		}
	}

	template<RectBaseType T>
	T TRect<T>::OppositeX() const
	{
		if constexpr (std::is_same_v<int, T>) {
			return x + width - Math::Sign(width);
		} else {
			return x + width;
		}
	}

	template<RectBaseType T>
	T TRect<T>::OppositeY() const
	{
		if constexpr (std::is_same_v<int, T>) {
			return y + height - Math::Sign(height);
		} else {
			return y + height;
		}
	}

	template<RectBaseType T>
	bool TRect<T>::IsFlipedX() const
	{
		return width < 0;
	}

	template<RectBaseType T>
	bool TRect<T>::IsFlipedY() const
	{
		return height < 0;
	}

	template<RectBaseType T>
	bool TRect<T>::IsFliped() const
	{
		return IsFlipedX() || IsFlipedY();
	}

	template<RectBaseType T>
	void TRect<T>::FlipX()
	{
		x = OppositeX();
		width = -width;
	}

	template<RectBaseType T>
	void TRect<T>::FlipY()
	{
		y = OppositeY();
		height = -height;
	}

	template<RectBaseType T>
	void TRect<T>::UnFlip()
	{
		if (IsFlipedX()) {
			FlipX();
		}

		if (IsFlipedY()) {
			FlipY();
		}
	}

	template<RectBaseType T>
	bool TRect<T>::Contain(const TVector2<T>& point) const
	{
		if (point.x < x || point.y < y) {
			return false;
		}

		if (point.x > OppositeX() || point.y > OppositeY()) {
			return false;
		}

		return true;
	}

	template<RectBaseType T>
	bool TRect<T>::ContainWithSafeCheck(const TVector2<T>& point) const
	{
		if (IsEmpty()) {
			return false;
		}

		TRect copy = *this;
		copy.UnFlip();
		return copy.Contain(point);
	}

	template<RectBaseType T>
	bool TRect<T>::Overlap(const TRect<T>& other) const
	{
		return Overlap(*this, other);
	}

	template<RectBaseType T>
	bool TRect<T>::Overlap(const TRect<T>& first, const TRect<T>& second)
	{
		TVector2<T> firstOpposite(first.OppositeX(), first.OppositeY());
		TVector2<T> secondOpposite(second.OppositeX(), second.OppositeY());

		if (first.x > secondOpposite.x || first.y > secondOpposite.y ||
			second.x > firstOpposite.x || second.y > firstOpposite.y) {
			return false;
		}
		return true;
	}

	template<RectBaseType T>
	bool TRect<T>::OverlapWithSafeCheck(const TRect& other) const
	{
		return OverlapWithSafeCheck(*this, other);
	}

	template<RectBaseType T>
	bool TRect<T>::OverlapWithSafeCheck(const TRect& first, const TRect& second)
	{
		if (first.IsEmpty() || second.IsEmpty()) {
			return false;
		}

		TRect firstCopy = first;
		TRect secondCopy = second;
		firstCopy.UnFlip();
		secondCopy.UnFlip();
		return Overlap(firstCopy, secondCopy);
	}

	template<RectBaseType T>
	TRect<T>& TRect<T>::Move(const TVector2<T>& offset)
	{
		x += offset.x;
		y += offset.y;
		return *this;
	}

	template<RectBaseType T>
	TRect<T> TRect<T>::GetMinOuterRect(const TRect& innerRect, float rotateDegreeFromCenter)
	{
		if (rotateDegreeFromCenter == 0.0f) {
			return innerRect;
		}

		float radian = Math::ToRadian(rotateDegreeFromCenter);
		float sinValue = std::sin(radian);
		float cosValue = std::cos(radian);

		float width = std::abs(innerRect.width * cosValue) + std::abs(innerRect.height * sinValue);
		float height = std::abs(innerRect.width * sinValue) + std::abs(innerRect.height * cosValue);

		if constexpr (std::is_same_v<int, T>) {
			float centerXFloat = innerRect.x + innerRect.width / 2.0f;
			float centerYFloat = innerRect.y + innerRect.height / 2.0f;

			int resultX = (int)std::floorf(-width / 2.0f + centerXFloat);
			int resultY = (int)std::floorf(-height / 2.0f + centerYFloat);
			int resultOppositeX = (int)std::ceilf(width / 2.0f + centerXFloat);
			int resultOppositeY = (int)std::ceilf(height / 2.0f + centerYFloat);

			return FromDiagonal(resultX, resultY, resultOppositeX, resultOppositeY);
		} else {
			TRect result = FromCenter(width, height);
			result.Move(innerRect.Center());
			return result;
		}
	}

	template<RectBaseType T>
	TRect<T>::operator TRect<float>() const requires (!std::is_same_v<float, T>)
	{
		return TRect<float>((float)x, (float)y, (float)width, (float)height);
	}

#pragma endregion

#pragma region Explicit Instantiation Definition

	template struct TRect<int>;
	template struct TRect<float>;

#pragma endregion
}