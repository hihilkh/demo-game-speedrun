#include "GE/GEHeader.h"
#include "MapObject.h"
#include "Map/MapSizeInfo.h"

namespace Map
{
	MapObject::MapObject(GameObject& gameObject, MapObjectType type) :
		Component(gameObject),
		type(type)
	{
	}

	void MapObject::SetPos(const Vector2Int& grid)
	{
		GetTransform().SetPos(ConvertPosFromGrid(grid));
	}
}