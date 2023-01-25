#include "MapChipFactory.h"

#include <cassert>

#include "Utils/Log.h"

#include "MapChip/MapChipBase.h"
#include "MapChip/FloorMapChip.h"
#include "MapChip/TransportBeltMapChip.h"
#include "MapChip/UnbreakableWallMapChip.h"
#include "MapChip/WeakWallMapChip.h"

#include "MapObject/MapObjectType.h"
#include "MapObject/Task_Goal.h"


namespace Map
{
	namespace
	{
		const int DirectionDivisor = 100;
		const int MapObjectDivisor = 1000;
	}

	shared_ptr<MapChipBase> GenerateMapChip(int typeId, shared_ptr<Resource> res, const ML::Box2D& hitBase)
	{
		int realTypeInt = typeId;
		Direction direction = Direction::Down;

		if (typeId >= DirectionDivisor) {
			realTypeInt = typeId % DirectionDivisor;

			int directionInt = typeId;
			if (typeId >= MapObjectDivisor) {
				directionInt %= MapObjectDivisor;
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
		}

		assert(false && "まだMapChipTypeの実装はない");

		// 警告を出さないように
		return make_shared<FloorMapChip>(res, hitBase);
	}

	void GenerateMapObject(int typeId, const ML::Box2D& hitBase)
	{
		if (typeId < MapObjectDivisor) {
			return;
		}

		int realTypeInt = typeId / MapObjectDivisor;

		MapObjectType type = static_cast<MapObjectType>(realTypeInt);

		switch (type) {
			case MapObjectType::Goal: {
				// TODO : Initを使わない方法を考える
				Goal::Object::SP goal = Goal::Object::Create(true);
				goal->Init(hitBase.x, hitBase.y);
				break;
			}
			default:
				PrintWarning("まだ MapObjectType:" << realTypeInt << " の実装はない");
				break;
		}
	}
}