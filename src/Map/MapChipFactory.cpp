#include "MapChipFactory.h"

#include <cassert>
#include "MapChipBase.h"

#include "FloorMapChip.h"
#include "TransportBeltMapChip.h"
#include "UnbreakableWallMapChip.h"
#include "WeakWallMapChip.h"

namespace Map
{
	namespace {
		const int DirectionDivisor = 100;
	}

	shared_ptr<MapChipBase> GenerateMapChip(int typeId, shared_ptr<Resource> res, const ML::Box2D& hitBase)
	{
		int realTypeInt = typeId;
		Direction direction = Direction::Down;

		if (typeId >= DirectionDivisor) {
			realTypeInt = typeId % DirectionDivisor;
			int directionInt = typeId / DirectionDivisor - 1;
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
}