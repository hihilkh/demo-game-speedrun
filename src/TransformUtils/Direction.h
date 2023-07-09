#pragma once

#include <stdint.h>
#include "GE/Utils/TypeDef.h"

namespace TransformUtils
{
	enum class Direction : std::uint8_t
	{
		Down = 0,
		Left = 1,
		Up = 2,
		Right = 3,
	};

	Direction GetOppositeDirection(Direction dir);
	Direction GetNextDirection(Direction dir, bool isClockwise);

	Vector2 GetDirectionalVector(Direction dir);

	/// <returns>
	/// <para>1 = 同じ方向</para>
	/// <para>-1 = 反対方向</para>
	/// <para>0 = 他</para>
	/// </returns>
	int CompareDirection(Direction dir1, Direction dir2);

	/// <summary>
	/// できれば、元のDirectionを維持する
	/// </summary>
	/// <param name="newDirVector">長さは1とは限らない</param>
	/// <returns></returns>
	Direction GetNewDirection(Direction previousDir, const Vector2& newDirVector);
}