#pragma once

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
		static void OnStartCollision();
	};
}