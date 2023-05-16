﻿#pragma once

#pragma region 前方宣言

namespace GE
{
	class GameObject;
	class Component;
	class Transform2D;
	struct Color;
	class Time;

	namespace DataType::Internal
	{
		template<typename T>
		struct TVector2;
		template<typename T>
		struct TVector3;

		template<typename T>
		struct TRect;
	}
}

#pragma endregion

#pragma region typedef

using GameObject	= GE::GameObject;
using Component		= GE::Component;
using Transform2D	= GE::Transform2D;
using Vector2		= GE::DataType::Internal::TVector2<float>;
using Vector2Int	= GE::DataType::Internal::TVector2<int>;
using Vector3		= GE::DataType::Internal::TVector3<float>;
using Vector3Int	= GE::DataType::Internal::TVector3<int>;
using Color			= GE::Color;

// 備考：
// 本質的に TRect<float> と TRect<int> は大きな違いがある。
// TRect<float> の場合、点はサイズがない。
// TRect<int> の場合、点が 1 x 1 のサイズとみなす。
// (参考：TRect::FromMinMax())
// そういうわけで、TRect<int> を RectInt ではなく、RectPixel と命名する。

using Rect			= GE::DataType::Internal::TRect<float>;
using RectPixel		= GE::DataType::Internal::TRect<int>;

// TODO : Utils/Timeの中の命名
//using Time = GE::Time;

#pragma endregion