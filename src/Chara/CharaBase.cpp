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

void CharaBase::AdjustMoveWithMap(const ML::Vec2& targetMove)
{
	if (!map) {
		PrintWarning("マップの参照がない。キャラクターは自由に移動できる");
		transform->pos = targetMove;
		return;
	}

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
				break;
			}
		}
	}
}