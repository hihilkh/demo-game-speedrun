#include "CollisionLayerMatrix.h"

namespace GE::Collision
{
	void CollisionLayerMatrix::AddCollisionRule(CollisionLayer::Bitmask layer, CollisionLayer::Bitmask targets)
	{
		CollisionLayer::Bitmask layerBelow = layer;
		CollisionLayer::Bitmask remainTargets = targets;

		// triangularMatrixの"triangular"を維持する。つまり、
		// key <= value
		// 例えば、
		// triangularMatrix[1] = 1 + 2 + 4 + 8
		// triangularMatrix[2] = 0 + 0 + 4 + 8
		// triangularMatrix[4] = 0 + 0 + 4 + 0
		// triangularMatrix[8] = 0 + 0 + 0 + 8
		while (layerBelow >>= 1, layerBelow > 0) {
			if ((remainTargets & layerBelow) == layerBelow) {
				triangularMatrix[layerBelow] |= layer;
				remainTargets &= ~layerBelow;
			}
		}

		triangularMatrix[layer] |= remainTargets;
	}

	CollisionLayer::Bitmask CollisionLayerMatrix::operator[](CollisionLayer::Bitmask layer) const 
	{ 
		auto pair = triangularMatrix.find(layer);
		if (pair == triangularMatrix.end()) {
			return CollisionLayer::none;
		}

		return pair->second;
	}
}