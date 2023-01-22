#pragma once

#pragma region 前方宣言

namespace ML {
	class Vec2;
}

#pragma endregion

enum class Direction : short {
	Down = 0,
	Left = 1,
	Up = 2,
	Right = 3,
};

ML::Vec2 GetDirectionalVector(Direction direction);

/// <returns>
/// <para>1 = 同じ方向</para>
/// <para>-1 = 反対方向</para>
/// <para>0 = 他</para>
/// </returns>
int CompareDirection(Direction direction1, Direction direction2);