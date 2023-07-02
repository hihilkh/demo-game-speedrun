#pragma once

#include "GE/Utils/TypeDef.h"
#include "Common/Direction.h"
#include "Tile/TileType.h"
#include "MapObject/MapObjectType.h"

namespace Map
{
	class Tile;
	class MapObject;
	struct MapCoreInfo;

	class MapFactory
	{


	public:
		explicit MapFactory(GameObject& mapBase);

		void Create(const Vector2Int& grid, int rawInfo, MapCoreInfo& mapCoreInfo) const;

	private:
		GameObject& mapBase;

	private:
		static Tile* InstantiateTile(TileType type, Direction direction);
		static MapObject* InstantiateMapObject(MapObjectType type);

		static void InsertMapCoreInfo(MapCoreInfo& mapCoreInfo, const Vector2Int& grid, MapObjectType type);
	};
}