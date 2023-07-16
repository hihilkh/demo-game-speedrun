#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "GE/DataType/Rect.h"

namespace Player
{
	class PlayerModel;

	class PlayerCollisionHandler : public Component
	{
	public:
		PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, RectCollider& collider);

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
		RectCollider& collider;

		bool isCachedCollisionInfo;
		bool isOverCrashSpeed;
		Rect facingDirMovementRect;

	private:
		void HandleCollision(const Collider& other, CollidedType collidedType);
		CollisionTypeWhileRunning CheckCollisionTypeWhileRunning(const Collider& other);
		void CacheCollisionInfo();
	};
}