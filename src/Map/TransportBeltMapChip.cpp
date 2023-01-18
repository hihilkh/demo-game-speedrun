﻿#include "TransportBeltMapChip.h"

namespace Map
{
	TransportBeltMapChip::TransportBeltMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase, Direction direction) :
		MapChipBase::MapChipBase(MapChipType::TransportBelt, res, hitBase),
		direction(direction)
	{

	}

	TransportBeltMapChip::~TransportBeltMapChip()
	{

	}

	// TODO : Think of use design pattern and do it in res
	ML::Box2D TransportBeltMapChip::GetRenderSrc() const
	{
		// TODO
		switch (direction) {
			case Direction::Down:
			case Direction::Left:
			case Direction::Up:
			case Direction::Right:
			default:
				return ML::Box2D(0, 64, 32, 32);
		}
	}

	bool TransportBeltMapChip::GetIsWalkable() const
	{
		return true;
	}
}