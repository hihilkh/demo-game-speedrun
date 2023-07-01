#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	struct CollisionRecordImpl
	{
		Vector2 posOffset;

		explicit CollisionRecordImpl(const Vector2& posOffset) : posOffset(posOffset) {}
	};
}