#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace GE::Collision
{
	class Collider;
}

namespace Player
{
	class PlayerModel;

	class PlayerCollisionHandler : public Component
	{
	public:
		PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, GE::Collision::Collider& collider);

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		PlayerModel& model;
		GE::Collision::Collider& collider;

	private:
		void HandleCollision(const GE::Collision::Collider& other);
		bool CheckIsCrash(const GE::Collision::Collider& other) const;
	};
}