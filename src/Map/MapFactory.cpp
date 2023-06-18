#include "GE/GEHeader.h"
#include "MapFactory.h"
#include "GE/Utils/EnumUtils.h"

#include "Tile/TileBase.h"

#include "Tile/FloorTile.h" 
#include "Prefab/Map/Tile/FloorTilePrefab.h"

#include "Tile/TransportBeltTile.h" 
#include "Prefab/Map/Tile/TransportBeltTilePrefab.h"

#include "Tile/UnbreakableWallTile.h" 
#include "Prefab/Map/Tile/UnbreakableWallTilePrefab.h"

#include "Tile/WeakWallTile.h" 
#include "Prefab/Map/Tile/WeakWallTilePrefab.h"


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

	void MapFactory::Create(const Vector2Int& pos, int rawInfo) const
	{
		int typeId = rawInfo;
		Direction direction = Direction::Down;

		if (rawInfo >= directionDivisor) {
			typeId = rawInfo % directionDivisor;

			int directionInt = rawInfo;
			if (rawInfo >= mapObjectDivisor) {
				directionInt %= mapObjectDivisor;
				GenerateMapObject(pos, rawInfo / mapObjectDivisor);
			}
			directionInt = directionInt / directionDivisor - 1;
			direction = static_cast<Direction>(directionInt);
		}

		TileType type = static_cast<TileType>(typeId);
		TileBase* tile = InstantiateTile(type, direction);
		if (tile) {
			tile->SetPos(pos);
		}
	}

	TileBase* MapFactory::InstantiateTile(TileType type, Direction direction)
	{
		switch (type) {
			case Map::TileType::Floor:
				return &GE::Instantiate(Prefab::Map::FloorTilePrefab());
			case Map::TileType::TransportBelt:
				return &GE::Instantiate(Prefab::Map::TransportBeltTilePrefab());
			case Map::TileType::UnbreakableWall:
				return &GE::Instantiate(Prefab::Map::UnbreakableWallTilePrefab());
			case Map::TileType::WeakWall:
				return &GE::Instantiate(Prefab::Map::WeakWallTilePrefab());
			default:
				DEBUG_LOG_WARNING("InstantiateTile : まだ TileType : " << GE::Enum::ToString(type) << " の実装はない");
				return nullptr;
		}
	}

	MapObjectBase* MapFactory::GenerateMapObject(const Vector2Int& pos, int mapObjectId) const
	{
		// TODO
		return nullptr;
	}

	// TODO
	/*
		void GenerateMapObject(int mapObjectId, const ML::Box2D& hitBase)
		{
			MapObjectType type = static_cast<MapObjectType>(mapObjectId);

			switch (type) {
				case MapObjectType::Player:
					Game::GameStatus::PlayerInitialPos = ML::Vec2((float)hitBase.x, (float)hitBase.y);
					break;
				case MapObjectType::Goal: {
					// TODO : Initを使わない方法を考える
					Goal::Object::SP goal = Goal::Object::Create(true);
					goal->Init(hitBase.x, hitBase.y);
					break;
				}
				default:
					DEBUG_LOG_WARNING("まだ MapObject の id:" << mapObjectId << " の実装はない");
					break;
			}
		}
	*/
}