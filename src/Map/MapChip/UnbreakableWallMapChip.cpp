#include "UnbreakableWallMapChip.h"

// TODO : delete
namespace Map
{
	UnbreakableWallMapChip::UnbreakableWallMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase) :
		MapChipBase::MapChipBase(MapChipType::UnbreakableWall, res, hitBase)
	{

	}

	UnbreakableWallMapChip::~UnbreakableWallMapChip()
	{

	}

	ML::Box2D UnbreakableWallMapChip::GetRenderSrc() const
	{
		return ML::Box2D(32, 0, 32, 32);
	}

	bool UnbreakableWallMapChip::GetIsWalkable() const
	{
		return false;
	}
}