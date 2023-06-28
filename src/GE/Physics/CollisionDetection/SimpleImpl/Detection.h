#pragma once

#include "../ColliderTypeDef.h"
#include "GE/Utils/TypeDef.h"
#include "../CollidedType.h"

namespace GE::Physics::CollisionDetection::SimpleImpl
{
	CollidedType CheckCollision(const RectCollider& lhs, const RectCollider& rhs);
	CollidedType CheckCollision(const Rect& lhsRect, float lhsRot, const Rect& rhsRect, float rhsRot);

	/// <summary>
	/// この関数は、渡したcollider同士が重なっていると想定する
	/// </summary>
	void RecordCollisionAdjustment(RectCollider& lhs, RectCollider& rhs);

}