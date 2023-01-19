#include "CharaBase.h"
#include "Utils/Log.h"
#include "Map/Task_Map.h"

namespace Chara
{
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

	ML::Vec2 CharaBase::GetDirectionalVector(Direction direction) const
	{
		switch (direction) {
			case Direction::Left:	return ML::Vec2(-1, 0);
			case Direction::Right:	return ML::Vec2(1, 0);
			case Direction::Up:		return ML::Vec2(0, -1);
			case Direction::Down:	return ML::Vec2(0, 1);
		}

		assert(false && "おかしい方向");

		// 警告を出さないように
		return ML::Vec2(0, 0);
	}

	ML::Box2D CharaBase::GetCurrentHitBox() const
	{
		return hitBase.OffsetCopy(transform->pos);
	}

#pragma region 移動の流れ

	void CharaBase::UpdateMovement()
	{
		ML::Vec2 targetMove = PreMove();
		bool isHit = CheckMapCollisionAndMove(targetMove);
		if (isHit) {
			CollideWithMap();
		}

		CheckMapTrigger();
		PostMove();
	}

	ML::Vec2 CharaBase::PreMove()
	{
		return ML::Vec2();
	}

	bool CharaBase::CheckMapCollisionAndMove(const ML::Vec2& targetMove)
	{
		if (!map) {
			PrintWarning("マップの参照がない。キャラクターは自由に移動できる");
			transform->pos = targetMove;
			return false;
		}

		bool isCollide = false;

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

				if (map->CheckCollision(*this)) {
					*pAxisValue = previousValue;		//移動をキャンセル
					isCollide = true;
					break;
				}
			}
		}

		return isCollide;
	}

	void CharaBase::CollideWithMap()
	{
	}

	void CharaBase::CheckMapTrigger()
	{
		if (!map) {
			return;
		}

		map->CheckTrigger(*this);
	}

	void CharaBase::PostMove()
	{
	}

#pragma endregion

}