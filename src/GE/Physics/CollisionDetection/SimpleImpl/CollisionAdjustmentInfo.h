#pragma once

#include <vector>
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE::Physics::CollisionDetection::SimpleImpl
{
	class CollisionAdjustmentInfo
	{
	public:
		void AddInfo(float xOffset, float yOffset);
		Vector2 CalculateAdjustmentAndClearInfos();

	private:
		// 一つのinfoはVector2型で、posXのoffset または(つまり、or) posYのoffsetが必要だと表す
		// infosの中の全てのinfoも必要である(つまり、and)
		// infoの二つの値も0になるわけがないと想定する
		std::vector<Vector2> infos;
	};
}