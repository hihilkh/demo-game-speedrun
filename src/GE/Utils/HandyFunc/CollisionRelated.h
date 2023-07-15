#pragma once

#include "GE/Collision/Detection/CollidedType.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"

namespace GE::Collision
{
	Detection::CollidedType CheckCollision(
		const Rect& lhsRect,
		const Rect& rhsRect,
		float lhsRot,
		float rhsRot);
}