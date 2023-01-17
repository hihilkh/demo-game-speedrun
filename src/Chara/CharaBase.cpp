#include "CharaBase.h"
#include "Utils/Log.h"
#include "Game/Task_Map.h"

CharaBase::CharaBase(const ML::Box2D& hitBase) : CharaBase::CharaBase(ML::Vec2(), hitBase)
{

}

CharaBase::CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase) :
	transform(make_shared<Transform>(pos)),
	hitBase(hitBase),
	moveVec(ML::Vec2()),
	moveCnt(0),
	direction(Direction::Down)
{

}

bool CharaBase::AdjustMoveWithMap(const ML::Vec2& targetMove)
{
	if (!map) {
		PrintWarning("マップの参照がない。キャラクターは自由に移動できる");
		transform->pos = targetMove;
		return false;
	}

	bool isHit = false;

	const int noOfAxis = 2;
	float* pMoveAxisValues[noOfAxis] = { &transform->pos.x, &transform->pos.y };
	float targetAxisMoves[noOfAxis] = { targetMove.x, targetMove.y };

	for (int i = 0; i < noOfAxis; ++i) {
		float* pAxisValue = pMoveAxisValues[i];
		float move = targetAxisMoves[i];

		while (move != 0) {
			float previousValue = *pAxisValue;
			if (move >= 1) {
				++(*pAxisValue);
				--move;
			}
			else if (move <= -1) {
				--(*pAxisValue);
				++move;
			}
			else {
				*pAxisValue += move;
				move = 0;
			}

			ML::Box2D hit = hitBase.OffsetCopy(transform->pos);
			if (map->CheckHit(hit)) {
				*pAxisValue = previousValue;		//移動をキャンセル
				isHit = true;
				break;
			}
		}
	}

	return isHit;
}

ML::Vec2 CharaBase::GetDirectionalVector(Direction direction) const
{
	switch (direction) {
		case Direction::Left:	return ML::Vec2(-1, 0);
		case Direction::Right:	return ML::Vec2(1, 0);
		case Direction::Up:		return ML::Vec2(0, -1);
		case Direction::Down:	return ML::Vec2(0, 1);
	}

	assert(false && "おかしい方向");
}