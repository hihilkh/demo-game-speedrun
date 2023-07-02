#include "GE/GEHeader.h"
#include "MapSizeInfo.h"

namespace Map
{
	Vector2 ConvertPosFromGrid(const Vector2Int& grid)
	{
		return Vector2((float)(tileWidth * grid.x), (float)(tileHeight * grid.y));
	}
}