#pragma once

#include "Impl/WindowsKeyCode.h"

namespace GE::Input
{
	struct Key
	{
		// 十字キー
		static const KeyCode left, right, up, down;
		// 特殊文字
		static const KeyCode spaceKey, returnKey;
		// 数字
		static const KeyCode zero, one, two, three, four, five, six, seven, eight, nine;
		// 英文字
		static const KeyCode a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
	};
}