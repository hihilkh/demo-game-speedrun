#pragma once

#include <myLib.h>
#include "Direction.h"

class Transform
{
public:
	ML::Vec2 pos;
	Direction direction;

	explicit Transform(const ML::Vec2& pos, Direction direction);
	~Transform() {}

	typedef shared_ptr<Transform> SP;
	typedef weak_ptr<Transform> WP;
};