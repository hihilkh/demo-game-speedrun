#include "UnbreakableWallMapChip.h"

namespace Map
{
	UnbreakableWallMapChip::UnbreakableWallMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase) :
		MapChipBase::MapChipBase(MapChipType::UnbreakableWall, res, hitBase)
	{

	}

	UnbreakableWallMapChip::~UnbreakableWallMapChip()
	{

	}

	// TODO : Think of use design pattern and do it in res
	ML::Box2D UnbreakableWallMapChip::GetRenderSrc() const
	{
		return ML::Box2D(0, 32, 32, 32);
	}
}