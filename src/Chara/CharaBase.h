#pragma once

#include <myLib.h>
#include "Common/Transform.h"
#include "Common/Direction.h"

#pragma region 前方宣言

namespace Map { class Object; }

#pragma endregion

namespace Chara
{
	class CharaBase
	{
	protected:
		CharaBase(const ML::Box2D& hitBase, const ML::Box2D& renderBase);
		CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase, const ML::Box2D& renderBase);

	public:
		virtual ~CharaBase() {}

	protected:
		struct AdditionalSpeedInfo
		{
			bool isActive;		// falseの場合は、AdditionalSpeedを処理しない
			Direction direction;
			float speed;

			AdditionalSpeedInfo() : isActive(false), direction(Direction::Down), speed(0.0f)
			{
			}

			ML::Vec2 GetCurrentSpeedVector()
			{
				return GetDirectionalVector(direction) * speed;
			}
		};

		ML::Box2D hitBase;
		ML::Box2D renderBase;
		ML::Vec2 moveVec;
		int moveCnt;
		float currentMovementSpeed;		// Inputによっての速度（AdditionalSpeedによる影響もある）。実際の速度ではない。
		AdditionalSpeedInfo additionalSpeedInfo;

		shared_ptr<Map::Object> map;

	public:
		Transform::SP transform;

	protected:

#pragma region 移動の流れ

		void UpdateMovement();

		/// <returns>targetMove</returns>
		virtual ML::Vec2 PreMove();
		void CheckMapTrigger();
		void HandleAdditionalSpeed(ML::Vec2& outTargetMove);
		/// <returns>ぶつかったかどうか</returns>
		bool CheckMapCollisionAndMove(const ML::Vec2& targetMove);
		virtual void CollideWithMap();
		virtual void PostMove();

#pragma endregion

		ML::Box2D GetCurrentRenderBox() const;

	public:
		ML::Box2D GetCurrentHitBox() const;

		void SetAdditionalSpeedInfo(Direction direction, float speed);
	};
}