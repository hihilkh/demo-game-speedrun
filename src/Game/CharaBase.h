﻿#pragma once

#include "myLib.h"
#include "Common/Transform.h"

#pragma region 前方宣言

namespace Map { class Object; }

#pragma endregion

class CharaBase
{
public:
	enum class Direction { Left, Right };

protected:
	ML::Box2D hitBase;
	ML::Vec2 moveVec;
	int moveCnt;
	Direction direction;

	shared_ptr<Map::Object> map;

	CharaBase(const ML::Box2D& hitBase);
	CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase);

public:
	Transform::SP transform;

public:
	virtual ~CharaBase() {}

	void AdjustMoveWithMap(const ML::Vec2& targetDest);
};