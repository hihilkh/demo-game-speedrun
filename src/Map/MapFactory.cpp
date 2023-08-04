#include "GE/GEHeader.h"
#include "MapFactory.h"
#include "GE/Utils/EnumUtils.h"
#include "MapCoreInfo.h"
#include "MapSizeInfo.h"

#include "Tile/Tile.h"
#include "MapObject/MapObject.h"

#include "Tile/FloorTile.h" 
#include "Prefab/Map/Tile/FloorTilePrefab.h"

#include "Tile/TransportBeltTile.h" 
#include "Prefab/Map/Tile/TransportBeltTilePrefab.h"

#include "Tile/UnbreakableWallTile.h" 
#include "Prefab/Map/Tile/UnbreakableWallTilePrefab.h"

#include "Tile/WeakWallTile.h" 
#include "Prefab/Map/Tile/WeakWallTilePrefab.h"

#include "MapObject/GoalObject.h" 
#include "Prefab/Map/MapObject/GoalObjectPrefab.h"


// TODO : マップデータの仕組みを改善
// TODO : パフォーマンスの改善を考える
// - 参考：https://zenn.dev/tardigrader/articles/d0c39793aa3719
// - UnityのtileMapのように一括管理するか？
namespace Map
{
	namespace
	{
		const int directionDivisor = 100;
		const int mapObjectDivisor = 1000;
	}

	MapFactory::MapFactory(GameObject& mapBase) : mapBase(mapBase)
	{
	}

	void MapFactory::Create(const Vector2Int& grid, int rawInfo, MapCoreInfo& mapCoreInfo) const
	{
		int typeId = rawInfo;
		TransformUtils::Direction direction = TransformUtils::Direction::Down;

		if (rawInfo >= directionDivisor) {
			typeId = rawInfo % directionDivisor;

			int directionInt = rawInfo;
			if (rawInfo >= mapObjectDivisor) {
				directionInt %= mapObjectDivisor;

				MapObjectType type = static_cast<MapObjectType>(rawInfo / mapObjectDivisor);
				MapObject* mapObject = InstantiateMapObject(type);
				if (mapObject) {
					mapObject->SetPos(grid);
				}
				InsertMapCoreInfo(mapCoreInfo, grid, type);
			}
			directionInt = directionInt / directionDivisor - 1;
			direction = static_cast<TransformUtils::Direction>(directionInt);
		}

		TileType type = static_cast<TileType>(typeId);
		Tile* tile = InstantiateTile(type, direction);
		if (tile) {
			tile->SetPos(grid);
			tile->gameObject.SetIsStatic(true, true);
		}
	}

	Tile* MapFactory::InstantiateTile(TileType type, TransformUtils::Direction direction)
	{
		switch (type) {
			case Map::TileType::Floor:
				return &GE::Instantiate(Prefab::Map::FloorTilePrefab());
			case Map::TileType::TransportBelt: {
				auto& transportBelt = GE::Instantiate(Prefab::Map::TransportBeltTilePrefab());
				transportBelt.SetDirection(direction);
				return &transportBelt;
			}
			case Map::TileType::UnbreakableWall:
				return &GE::Instantiate(Prefab::Map::UnbreakableWallTilePrefab());
			case Map::TileType::WeakWall:
				return &GE::Instantiate(Prefab::Map::WeakWallTilePrefab());
			default:
				DEBUG_LOG_WARNING("InstantiateTile : まだ TileType::" << GE::Enum::ToString(type) << " の実装はない");
				return nullptr;
		}
	}

	MapObject* MapFactory::InstantiateMapObject(MapObjectType type)
	{
		switch (type) {
			case Map::MapObjectType::Player:
				return nullptr;
			case Map::MapObjectType::Goal:
				return &GE::Instantiate(Prefab::Map::GoalObjectPrefab());
			default:
				DEBUG_LOG_WARNING("InstantiateMapObject : まだ MapObjectType::" << GE::Enum::ToString(type) << " の実装はない");
				return nullptr;
		}
	}

	void MapFactory::InsertMapCoreInfo(MapCoreInfo& mapCoreInfo, const Vector2Int& grid, MapObjectType type)
	{
		switch (type) {
			case Map::MapObjectType::Player:
				mapCoreInfo.playerStartPos = ConvertPosFromGrid(grid);
				return;
			case Map::MapObjectType::Goal:
				mapCoreInfo.goalPos = ConvertPosFromGrid(grid);
				return;
		}
	}
}