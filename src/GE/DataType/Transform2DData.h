#pragma once

#include "GE/Utils/TypeDef.h"
#include "Vector2.h"

namespace GE
{
	// 備考：
	// もしscaleがあったら、せん断写像(shear mapping)のようなこともできなければならない。
	// (例：parent：scale.x = 2, child：rot = 45)
	// そういうわけで、scaleを支援しない
	struct Transform2DData
	{
		Vector2 pos;
		float rot;	// 度数法

		Transform2DData(const Vector2& pos, float rot) : pos(pos), rot(rot) {}
		virtual ~Transform2DData() = default;
	};
}