#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace Map
{
	inline const int tileWidth = 64;
	inline const int tileHeight = 64;

	Vector2 ConvertPosFromGrid(const Vector2Int& grid);
}