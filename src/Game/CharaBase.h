#pragma once

#include "Task_Map.h"

class CharaBase
{
public:
	enum class Direction { Left, Right };

protected:
	ML::Vec2 pos;
	ML::Box2D hitBase;
	ML::Vec2 moveVec;
	int moveCnt;
	Direction direction;

	Map::Object::SP map;

	CharaBase(const ML::Box2D& hitBase);
	CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase);

public:
	virtual ~CharaBase() {}

	void AdjustMoveWithMap(const ML::Vec2& targetDest);
};