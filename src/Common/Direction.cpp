#include "Direction.h"
#include <cassert>
#include <myLib.h>

ML::Vec2 GetDirectionalVector(Direction direction)
{
	switch (direction) {
		case Direction::Left:	return ML::Vec2(-1, 0);
		case Direction::Right:	return ML::Vec2(1, 0);
		case Direction::Up:		return ML::Vec2(0, -1);
		case Direction::Down:	return ML::Vec2(0, 1);
	}

	assert(false && "おかしい方向");

	// 警告を出さないように
	return ML::Vec2(0, 0);
}

int CompareDirection(Direction direction1, Direction direction2)
{
	short direction1Int = static_cast<short>(direction1);
	short direction2Int = static_cast<short>(direction2);
	if (direction1Int % 2 == direction2Int % 2) {
		return direction1Int == direction2Int ? 1 : -1;
	}

	return 0;
}