#pragma once

#include "myLib.h"
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
		ML::Box2D hitBase;
		ML::Vec2 moveVec;
		int moveCnt;
		Direction direction;

		shared_ptr<Map::Object> map;

		CharaBase(const ML::Box2D& hitBase);
		CharaBase(const ML::Vec2& pos, const ML::Box2D& hitBase);

	public:
		Transform::SP transform;

	protected:
		ML::Vec2 GetDirectionalVector(Direction direction) const;

#pragma region 移動の流れ

		void UpdateMovement();

		/// <returns>targetMove</returns>
		virtual ML::Vec2 PreMove();

		/// <returns>ぶつかったかどうか</returns>
		bool CheckMapCollisionAndMove(const ML::Vec2& targetMove);

		virtual void CollideWithMap();
		void CheckMapTrigger();
		virtual void PostMove();

#pragma endregion

	public:
		virtual ~CharaBase() {}

		Direction GetDirection() const { return direction; }

		ML::Box2D GetCurrentHitBox() const;
	};
}