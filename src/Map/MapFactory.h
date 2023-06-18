#pragma once

#include "GE/Utils/TypeDef.h"
#include "Common/Direction.h"
#include "Tile/TileType.h"

namespace Map
{
	class TileBase;
	class MapObjectBase;

	class MapFactory
	{
	public:
		explicit MapFactory(GameObject& mapBase);

		void Create(const Vector2Int& pos, int rawInfo) const;

	private:
		GameObject& mapBase;

	private:
		static TileBase* InstantiateTile(TileType type, Direction direction);
		MapObjectBase* GenerateMapObject(const Vector2Int& pos, int mapObjectId) const;
	};
}