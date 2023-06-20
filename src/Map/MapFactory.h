#pragma once

#include "GE/Utils/TypeDef.h"
#include "Common/Direction.h"
#include "Tile/TileType.h"

namespace Map
{
	class Tile;
	class MapObjectBase;

	class MapFactory
	{
	public:
		explicit MapFactory(GameObject& mapBase);

		void Create(const Vector2Int& pos, int rawInfo) const;

	private:
		GameObject& mapBase;

	private:
		static Tile* InstantiateTile(TileType type, Direction direction);
		MapObjectBase* GenerateMapObject(const Vector2Int& pos, int mapObjectId) const;
	};
}