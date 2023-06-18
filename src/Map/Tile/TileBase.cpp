#include "GE/GEHeader.h"
#include "TileBase.h"
#include "TileSize.h"

namespace Map
{
	TileBase::TileBase(GameObject& gameObject, TileType type) : 
		Component(gameObject), 
		type(type) 
	{
	}

	void TileBase::SetPos(const Vector2Int& pos)
	{
		GetTransform().pos.x = (float)(tileWidth * pos.x);
		GetTransform().pos.y = (float)(tileHeight * pos.y);
	}
}