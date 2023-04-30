#pragma once

//#include "Vector2.h"
//#include "Vector3.h"
//#include "Color.h"
//#include "Rect.h"

#pragma region 前方宣言

namespace GE
{
	struct Color;
	class Time;

	namespace Internal
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

typedef GE::Internal::TVector2<float>	Vector2;
typedef GE::Internal::TVector2<int>		Vector2Int;
typedef GE::Internal::TVector3<float>	Vector3;
typedef GE::Internal::TVector3<int>		Vector3Int;

typedef GE::Color						Color;


// 備考：
// 本質的に TRect<float> と TRect<int> は大きな違いがある。
// TRect<float> の場合、点はサイズがない。
// TRect<int> の場合、点が 1 x 1 のサイズとみなす。
// (参考：TRect::FromMinMax())
// そういうわけで、TRect<int> を RectInt ではなく、RectPixel と命名する。

typedef GE::Internal::TRect<float>		Rect;
typedef GE::Internal::TRect<int>		RectPixel;

// TODO : Utils/Timeの中の命名
//typedef GE::Time						Time;

#pragma endregion