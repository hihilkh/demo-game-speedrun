#pragma once

#include <vector>
#include "CollisionLayerMatrix.h"

namespace GE
{
	class GameEngine;
}

namespace GE::Physics
{
	class Collider;

	class CollisionSystem
	{
		friend GameEngine;

	public:
		static void AddCollider(Collider& collider);
		static void RemoveCollider(Collider& collider);

	private:
		static CollisionLayerMatrix collisionLayerMatrix;
		static std::vector<Collider*> colliders;

	private:
		static void OnStartCollision();
		static void SetCollisionLayerMatrix(CollisionLayerMatrix&& matrix) { CollisionSystem::collisionLayerMatrix = std::move(matrix); }
	};
}