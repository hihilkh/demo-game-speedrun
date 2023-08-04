#pragma once

#include <unordered_map>
#include "CollisionLayer.h"

namespace GE::Collision
{
	class CollisionLayerMatrix
	{
	public:
		/// <param name="layer">一つのlayerだけ</param>
		/// <param name="targets">複数のlayers可</param>
		void AddCollisionRule(CollisionLayer::Bitmask layer, CollisionLayer::Bitmask targets);

		CollisionLayer::Bitmask operator[](CollisionLayer::Bitmask layer) const;

	private:
		std::unordered_map<CollisionLayer::Bitmask, CollisionLayer::Bitmask> triangularMatrix;

	};
}