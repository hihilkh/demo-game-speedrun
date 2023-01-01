#pragma once

#include <myLib.h>

class Transform
{
public:
	ML::Vec2 pos;

	explicit Transform(const ML::Vec2& pos);
	~Transform() {}

	typedef shared_ptr<Transform> SP;
	typedef weak_ptr<Transform> WP;
};