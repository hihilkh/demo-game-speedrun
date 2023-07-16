#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "GE/DataType/Rect.h"

namespace GE::Collision
{
	class Collider;
	class RectCollider;

	namespace Detection
	{
		enum class CollidedType : std::uint8_t;
	}
}

namespace Player
{
	class PlayerModel;

	class PlayerCollisionHandler : public Component
	{
	public:
		PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, GE::Collision::RectCollider& collider);

	protected:
		void Start() override;
		void Update() override;
		void PreDestroy() override;

	private:

		enum class CollisionTypeWhileRunning
		{
			Ignore,
			Hit,
			Crash,
		};

		PlayerModel& model;
		GE::Collision::RectCollider& collider;

		bool isCachedCollisionInfo;
		bool isOverCrashSpeed;
		Rect facingDirMovementRect;

	private:
		void HandleCollision(const GE::Collision::Collider& other, GE::Collision::Detection::CollidedType collidedType);
		CollisionTypeWhileRunning CheckCollisionTypeWhileRunning(const GE::Collision::Collider& other);
		void CacheCollisionInfo();
	};
}