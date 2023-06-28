#include "GE/GEHeader.h"
#include "CollisionInfo.h"
#include "GE/Physics/CollisionLayerMatrix.h"

namespace CollisionInfo
{
	GE::Physics::CollisionLayerMatrix CreateCollisionLayerMatrix()
	{
		GE::Physics::CollisionLayerMatrix matrix;

		matrix.AddCollisionRule(playerLayer, mapLayer | mapObjectLayer);

		return matrix;
	}
}