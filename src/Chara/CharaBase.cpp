#include "CharaBase.h"
#include "Utils/Log.h"
#include "Map/Task_Map.h"

namespace Chara
{
	CharaBase::CharaBase(const ML::Box2D& hitBase, const ML::Box2D& renderBase) : CharaBase::CharaBase(ML::Vec2(), hitBase, renderBase)
	{

	}

	CharaBase::CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase, const ML::Box2D& renderBase) :
		transform(make_shared<Transform>(pos, Direction::Down)),
		hitBase(hitBase),
		renderBase(renderBase),
		moveVec(ML::Vec2()),
		moveCnt(0),
		currentMovementSpeed(0.0f),
		additionalSpeedInfo(AdditionalSpeedInfo())
	{

	}

	ML::Box2D CharaBase::GetCurrentRenderBox() const
	{
		return renderBase.OffsetCopy(transform->pos);
	}

	ML::Box2D CharaBase::GetCurrentHitBox() const
	{
		return hitBase.OffsetCopy(transform->pos);
	}

#pragma region 移動の流れ

	void CharaBase::UpdateMovement()
	{
		CheckMapTrigger();
		ML::Vec2 targetMove = PreMove();
		HandleAdditionalSpeed(targetMove);

		vector<Direction> collidedDirections = CheckMapCollisionAndMove(targetMove);
		if (collidedDirections.size() > 0) {
			CollidedWithMap(collidedDirections);
		}
		PostMove();
	}

	ML::Vec2 CharaBase::PreMove()
	{
		return ML::Vec2();
	}

	void CharaBase::HandleAdditionalSpeed(ML::Vec2& outTargetMove)
	{
		if (!additionalSpeedInfo.isActive) {
			return;
		}

		outTargetMove += additionalSpeedInfo.GetCurrentSpeedVector();
		currentMovementSpeed += additionalSpeedInfo.speed * CompareDirection(transform->direction, additionalSpeedInfo.direction);

		additionalSpeedInfo.isActive = false;
	}

	vector<Direction> CharaBase::CheckMapCollisionAndMove(const ML::Vec2& targetMove)
	{
		vector<Direction> collidedDirections;

		auto mapSP = map.lock();
		if (!mapSP) {
			PrintWarning("マップの参照がない。キャラクターは自由に移動できる");
			transform->pos = targetMove;
			return collidedDirections;
		}

		enum Axis { X = 0, Y = 1, End = 2 };
		float* pMoveAxisValues[Axis::End] = { &transform->pos.x, &transform->pos.y };
		float targetAxisMoves[Axis::End] = { targetMove.x, targetMove.y };

		for (int i = 0; i < Axis::End; ++i) {
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

				if (mapSP->CheckCollision(*this)) {
					float movedValue = *pAxisValue - previousValue;
					switch (i) {
						case Axis::X:
							collidedDirections.push_back(movedValue > 0 ? Direction::Left : Direction::Right);
							break;
						case Axis::Y:
							collidedDirections.push_back(movedValue > 0 ? Direction::Up : Direction::Down);
							break;
					}
					*pAxisValue = previousValue;		//移動をキャンセル
					break;
				}
			}
		}

		return collidedDirections;
	}

	void CharaBase::CollidedWithMap(const vector<Direction>& collidedDirections)
	{
	}

	void CharaBase::CheckMapTrigger()
	{
		if (auto mapSP = map.lock()) {
			mapSP->CheckTrigger(*this);
		}
	}

	void CharaBase::PostMove()
	{
	}

#pragma endregion

	void CharaBase::SetAdditionalSpeedInfo(Direction direction, float speed)
	{
		additionalSpeedInfo.isActive = true;
		additionalSpeedInfo.direction = direction;
		additionalSpeedInfo.speed = speed;
	}
}