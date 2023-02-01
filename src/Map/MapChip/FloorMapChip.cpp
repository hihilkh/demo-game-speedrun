#include "FloorMapChip.h"

namespace Map
{
	FloorMapChip::FloorMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase) :
		MapChipBase::MapChipBase(MapChipType::Floor, res, hitBase)
	{

	}

	FloorMapChip::~FloorMapChip()
	{

	}

	// TODO : resの中でデザインパターンで処理できるか？
	ML::Box2D FloorMapChip::GetRenderSrc() const
	{
		return ML::Box2D(0, 0, 32, 32);
	}

	bool FloorMapChip::GetIsWalkable() const
	{
		return true;
	}
}