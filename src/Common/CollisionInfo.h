#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Physics/CollisionLayer.h"

namespace GE::Physics
{
	class CollisionLayerMatrix;
}

namespace CollisionInfo
{
	inline const CollisionLayer::Bitmask mapLayer		= 1 << 1;
	inline const CollisionLayer::Bitmask mapObjectLayer = 1 << 2;
	inline const CollisionLayer::Bitmask playerLayer	= 1 << 3;

	GE::Physics::CollisionLayerMatrix CreateCollisionLayerMatrix();
}