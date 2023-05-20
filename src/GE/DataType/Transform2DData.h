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
		/// <summary>
		/// x : 正数：右
		/// y : 正数：上
		/// </summary>
		Vector2 pos;

		/// <summary>
		/// 度数法。正数：反時計回り
		/// </summary>
		float rot;

		Transform2DData(const Vector2& pos, float rot) : pos(pos), rot(rot) {}
		Transform2DData() : Transform2DData(Vector2::zero, 0.0f) {}

		virtual ~Transform2DData() = default;
	};
}