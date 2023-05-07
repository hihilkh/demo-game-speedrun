#pragma once

#include <iostream>
#include "Vector2.h"
#include <type_traits>
#include "Utils/Math.h"

namespace GE::DataType::Internal
{
#pragma region 宣言
	template<typename T>
	struct TRect
	{
		static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "The type must be int or float");

		union
		{
			struct { T x, y; };
			TVector2<T> pos;
		};
		union
		{
			struct { T width, height; };
			TVector2<T> size;
		};

		TRect();
		TRect(T x, T y, T width, T height);

		static TRect FromCenter(T width, T height);
		static TRect FromDiagonal(T x, T y, T oppositeX, T oppositeY);
		static TRect FromDiagonal(const TVector2<T>& point, const TVector2<T>& oppositePoint);

		T Area() const;
		TVector2<T> Center() const;
		bool IsEmpty() const;
		/// <summary>
		/// <para>xの反対側 (一般的にはRectの中にいる。例外：IsEmpty() == trueの場合)</para>
		/// IsEmpty() == trueかつwidth == 0の時、xの値を戻る
		/// </summary>
		T OppositeX() const;
		/// <summary>
		/// <para>yの反対側 (一般的にはRectの中にいる。例外：IsEmpty() == trueの場合)</para>
		/// IsEmpty() == trueかつheight == 0の時、yの値を戻る
		/// </summary>
		T OppositeY() const;

		/// <summary>
		/// x軸に沿って反転しているか
		/// </summary>
		bool IsFlipedX() const;
		/// <summary>
		/// y軸に沿って反転しているか
		/// </summary>
		bool IsFlipedY() const;
		/// <summary>
		/// x軸またはy軸に沿って反転しているか
		/// </summary>
		/// <returns></returns>
		bool IsFliped() const;

		/// <summary>
		/// x軸に沿って反転する。二回すると、元に戻す
		/// </summary>
		void FlipX();
		/// <summary>
		/// y軸に沿って反転する。二回すると、元に戻す
		/// </summary>
		void FlipY();
		/// <summary>
		/// 反転しない状態に戻す
		/// </summary>
		void UnFlip();

		/// <summary>
		/// <para>効率のために、下記のチェックを行わない(つまり、「普通」のRectと仮定する)：</para>
		/// <para>- Rectは反転しているか</para>
		/// <para>- IsEmpty() == true か</para>
		/// チェックをおこないたい場合、ContainWithSafeCheck()を使う。
		/// </summary>
		bool Contain(const TVector2<T>& point) const;
		bool ContainWithSafeCheck(const TVector2<T>& point) const;

		/// <summary>
		/// <para>効率のために、下記のチェックを行わない(つまり、「普通」のRectと仮定する)：</para>
		/// <para>- Rectは反転しているか</para>
		/// <para>- IsEmpty() == true か</para>
		/// チェックをおこないたい場合、OverlapWithSafeCheck()を使う。
		/// </summary>
		bool Overlap(const TRect& other) const;
		/// <summary>
		/// <para>効率のために、下記のチェックを行わない(つまり、「普通」のRectと仮定する)：</para>
		/// <para>- Rectは反転しているか</para>
		/// <para>- IsEmpty() == true か</para>
		/// チェックをおこないたい場合、OverlapWithSafeCheck()を使う。
		/// </summary>
		static bool Overlap(const TRect& first, const TRect& second);
		bool OverlapWithSafeCheck(const TRect& other) const;
		static bool OverlapWithSafeCheck(const TRect& first, const TRect& second);
	};

	template<typename T> bool operator==(const TRect<T>& lhs, const TRect<T>& rhs);
	template<typename T> bool operator!=(const TRect<T>& lhs, const TRect<T>& rhs);
	template<typename T> std::ostream& operator<<(std::ostream& os, const TRect<T>& rect);

#pragma endregion

#pragma region 関数定義

	template<typename T>
	inline TRect<T>::TRect() : TRect(T(), T(), T(), T())
	{
	}

	template<typename T>
	inline TRect<T>::TRect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
	{
	}

	template<typename T>
	inline TRect<T> TRect<T>::FromCenter(T width, T height)
	{
		return TRect(-(width / 2), -(height / 2), width, height);
	}

	template<typename T>
	inline TRect<T> TRect<T>::FromDiagonal(T x, T y, T oppositeX, T oppositeY)
	{
		T deltaX = oppositeX - x;
		T deltaY = oppositeY - y;

		if constexpr (std::is_integral_v<T>) {

			return TRect(x, y, deltaX + Math::SignNonZero(deltaX), deltaY + Math::SignNonZero(deltaY));
		} else {
			return TRect(x, y, deltaX, deltaY);
		}
	}

	template<typename T>
	inline TRect<T> TRect<T>::FromDiagonal(const TVector2<T>& point, const TVector2<T>& oppositePoint)
	{
		return FromMinMax(point.x, point.y, oppositePoint.x, oppositePoint.y);
	}

	template<typename T>
	inline T TRect<T>::Area() const
	{
		return width * height;
	}

	template<typename T>
	inline TVector2<T> TRect<T>::Center() const
	{
		return pos + size / T(2);
	}

	template<typename T>
	inline bool TRect<T>::IsEmpty() const
	{
		if constexpr (std::is_integral_v<T>) {
			return width == 0 || height == 0;
		} else {
			return false;
		}
	}

	template<typename T>
	inline T TRect<T>::OppositeX() const
	{
		if constexpr (std::is_integral_v<T>) {
			return x + width - Math::Sign(width);
		} else {
			return x + width;
		}
	}

	template<typename T>
	inline T TRect<T>::OppositeY() const
	{
		if constexpr (std::is_integral_v<T>) {
			return y + height - Math::Sign(height);
		} else {
			return y + height;
		}
	}

	template<typename T>
	inline bool TRect<T>::IsFlipedX() const
	{
		return width < 0;
	}

	template<typename T>
	inline bool TRect<T>::IsFlipedY() const
	{
		return height < 0;
	}

	template<typename T>
	inline bool TRect<T>::IsFliped() const
	{
		return IsFlipedX() || IsFlipedY();
	}

	template<typename T>
	inline void TRect<T>::FlipX()
	{
		x = OppositeX();
		width = -width;
	}

	template<typename T>
	inline void TRect<T>::FlipY()
	{
		y = OppositeY();
		height = -height;
	}

	template<typename T>
	inline void TRect<T>::UnFlip()
	{
		if (IsFlipedX()) {
			FlipX();
		}

		if (IsFlipedY()) {
			FlipY();
		}
	}

	template<typename T>
	inline bool TRect<T>::Contain(const TVector2<T>& point) const
	{
		if (point.x < x || point.y < y) {
			return false;
		}

		if (point.x > OppositeX() || point.y > OppositeY()) {
			return false;
		}

		return true;
	}

	template<typename T>
	inline bool TRect<T>::ContainWithSafeCheck(const TVector2<T>& point) const
	{
		if (IsEmpty()) {
			return false;
		}

		TRect copy = *this;
		copy.UnFlip();
		return copy.Contain(point);
	}

	template<typename T>
	inline bool TRect<T>::Overlap(const TRect<T>& other) const
	{
		return Overlap(*this, other);
	}

	template<typename T>
	inline bool TRect<T>::Overlap(const TRect<T>& first, const TRect<T>& second)
	{
		TVector2<T> firstOpposite(first.OppositeX(), first.OppositeY());
		TVector2<T> secondOpposite(second.OppositeX(), second.OppositeY());

		if (first.x > secondOpposite.x || first.y > secondOpposite.y ||
			second.x > firstOpposite.x || second.y > firstOpposite.y) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool TRect<T>::OverlapWithSafeCheck(const TRect& other) const
	{
		return OverlapWithSafeCheck(*this, other);
	}

	template<typename T>
	inline bool TRect<T>::OverlapWithSafeCheck(const TRect& first, const TRect& second)
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

	template<typename T>
	inline bool operator==(const TRect<T>& lhs, const TRect<T>& rhs)
	{
		return	lhs.pos == rhs.pos &&
				lhs.size == rhs.size;
	}

	template<typename T>
	inline bool operator!=(const TRect<T>& lhs, const TRect<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const TRect<T>& rect)
	{
		return os << "{ pos : " << rect.pos << " , size : " << rect.size << " }";
	}


#pragma endregion

}