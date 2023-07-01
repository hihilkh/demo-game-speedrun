#include "GE/GEHeader.h"
#include "CollisionInfo.h"
#include "GE/Collision/CollisionLayerMatrix.h"

namespace CollisionInfo
{
	GE::Collision::CollisionLayerMatrix CreateCollisionLayerMatrix()
	{
		GE::Collision::CollisionLayerMatrix matrix;

		matrix.AddCollisionRule(playerLayer, mapLayer | mapObjectLayer);

		return matrix;
	}
}