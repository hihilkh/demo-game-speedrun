#include "MapChipBase.h"
#include <cassert>

#include "FloorMapChip.h"
#include "UnbreakableWallMapChip.h"

// TODO : Study a proper way to do factory
namespace Map
{
	MapChipBase::SP GenerateMapChip(MapChipType type, shared_ptr<Resource> res, const ML::Box2D& hitBase)
	{
		switch (type) {
			case MapChipType::Floor:
				return make_shared<FloorMapChip>(res, hitBase);
			case MapChipType::UnbreakableWall:
				return make_shared<UnbreakableWallMapChip>(res, hitBase);
		}

		assert(false && "まだMapChipTypeの実装はない");
	}
}