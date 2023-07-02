#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace Map
{
	struct MapCoreInfo
	{
		Vector2 playerStartPos = Vector2::zero;
		Vector2 goalPos = Vector2::zero;
	};
}