#include "GE/GEHeader.h"
#include "Direction.h"

namespace TransformUtils
{
	Vector2 GetDirectionalVector(Direction dir)
	{
		switch (dir) {
			case Direction::Down:	return Vector2::down;
			case Direction::Left:	return Vector2::left;
			case Direction::Up:		return Vector2::up;
			case Direction::Right:	return Vector2::right;
		}

		assert(false && "おかしい方向");

		// 警告を出さないように
		return Vector2::zero;
	}

	Direction GetOppositeDirection(Direction dir)
	{
		auto dirInt = static_cast<std::uint8_t>(dir);
		dirInt += 2;
		dirInt %= 4;

		return static_cast<Direction>(dirInt);
	}

	Direction GetNextDirection(Direction dir, bool isClockwise)
	{
		auto dirInt = static_cast<std::uint8_t>(dir);
		dirInt += isClockwise ? 1 : 3;	// 備考：負数を避けるために、-1を使わない
		dirInt %= 4;

		return static_cast<Direction>(dirInt);
	}

	int CompareDirection(Direction dir1, Direction dir2)
	{
		if (dir1 == dir2) {
			return 1;
		}

		if (dir1 == GetOppositeDirection(dir2)) {
			return -1;
		}

		return 0;
	}

	Direction GetNewDirection(Direction previousDir, const Vector2& newDirVector)
	{
		if (newDirVector == Vector2::zero) {
			return previousDir;
		}

		float dot1 = Vector2::Dot(newDirVector, GetDirectionalVector(previousDir));
		if (dot1 > 0) {
			return previousDir;
		} else if (dot1 < 0) {
			return GetOppositeDirection(previousDir);
		} else {
			Direction nextDir = GetNextDirection(previousDir, true);
			float dot2 = Vector2::Dot(newDirVector, GetDirectionalVector(nextDir));
			return dot2 > 0 ? nextDir : GetOppositeDirection(nextDir);
		}
	}
}