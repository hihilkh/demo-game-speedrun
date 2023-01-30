#include "MapChipFactory.h"

#include "Utils/Log.h"

#include "MapChip/MapChipBase.h"
#include "MapChip/FloorMapChip.h"
#include "MapChip/TransportBeltMapChip.h"
#include "MapChip/UnbreakableWallMapChip.h"
#include "MapChip/WeakWallMapChip.h"

#include "MapObject/MapObjectType.h"
#include "MapObject/Task_Goal.h"

#include "Game/GameStatus.h"

// TODO : マップデータの仕組みを改善
namespace Map
{
	namespace
	{
		const int DirectionDivisor = 100;
		const int MapObjectDivisor = 1000;
	}

	namespace
	{
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
					PrintWarning("まだ MapObject の id:" << mapObjectId << " の実装はない");
					break;
			}
		}
	}

	shared_ptr<MapChipBase> GenerateMap(int typeId, shared_ptr<Resource> res, const ML::Box2D& hitBase)
	{
		int realTypeInt = typeId;
		Direction direction = Direction::Down;

		if (typeId >= DirectionDivisor) {
			realTypeInt = typeId % DirectionDivisor;

			int directionInt = typeId;
			if (typeId >= MapObjectDivisor) {
				directionInt %= MapObjectDivisor;
				GenerateMapObject(typeId / MapObjectDivisor, hitBase);
			}
			directionInt = directionInt / DirectionDivisor - 1;
			direction = static_cast<Direction>(directionInt);
		}

		MapChipType type = static_cast<MapChipType>(realTypeInt);

		switch (type) {
			case MapChipType::Floor:
				return make_shared<FloorMapChip>(res, hitBase);
			case MapChipType::TransportBelt:
				return make_shared<TransportBeltMapChip>(res, hitBase, direction);
			case MapChipType::UnbreakableWall:
				return make_shared<UnbreakableWallMapChip>(res, hitBase);
			case MapChipType::WeakWall:
				return make_shared<WeakWallMapChip>(res, hitBase);
			default:
				PrintWarning("まだ MapChip の id:" << realTypeInt << " の実装はない");
				return make_shared<FloorMapChip>(res, hitBase);
		}
	}
}