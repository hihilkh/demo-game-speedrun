#pragma once

#include <iostream>
#include "Vector2.h"
#include <type_traits>
#include "GE/Utils/GEConcept.h"

namespace GE::DataType::Internal
{
#pragma region TRectの宣言
	template<RectBaseType T>
	struct TRect
	{
		union
		{
			// 普通の場合、posは左下になる
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
		TRect(const TVector2<T>& pos, const TVector2<T>& size);

		static TRect FromCenter(T width, T height);
		static TRect FromCenter(const TVector2<T>& size);
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

		TRect& Move(const TVector2<T>& offset);

		static TRect GetAABB(const TRect& rect, float rotateDegreeFromCenter);

		// 暗黙的な変換
		operator TRect<float>() const requires (!std::is_same_v<float, T>);
	};

#pragma endregion

#pragma region operator オーバーロード

#pragma region 宣言

	template<RectBaseType T> bool operator==(const TRect<T>& lhs, const TRect<T>& rhs);
	template<RectBaseType T> bool operator!=(const TRect<T>& lhs, const TRect<T>& rhs);
	template<RectBaseType T> std::ostream& operator<<(std::ostream& os, const TRect<T>& rect);

#pragma endregion

#pragma region 定義

	template<RectBaseType T>
	bool operator==(const TRect<T>& lhs, const TRect<T>& rhs)
	{
		return	lhs.pos == rhs.pos &&
				lhs.size == rhs.size;
	}

	template<RectBaseType T>
	bool operator!=(const TRect<T>& lhs, const TRect<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<RectBaseType T>
	std::ostream& operator<<(std::ostream& os, const TRect<T>& rect)
	{
		return os << "{ pos : " << rect.pos << " , size : " << rect.size << " }";
	}

#pragma endregion

#pragma endregion

#pragma region Explicit Instantiation Declaration

	extern template struct TRect<int>;
	extern template struct TRect<float>;

#pragma endregion
}