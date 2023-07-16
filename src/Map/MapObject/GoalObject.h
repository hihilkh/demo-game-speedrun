#pragma once

#include "MapObject.h"
#include "GE/Core/Event.h"

namespace GE::Collision
{
	class Collider;
	namespace Detection
	{
		enum class CollidedType : std::uint8_t;
	}
}

namespace Map
{
	class GoalObject : public MapObject
	{
	public:
		static GE::Event<> onGoalReached;

	public:
		GoalObject(GameObject& gameObject, GE::Collision::Collider& collider);

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		GE::Collision::Collider& collider;

		bool isTriggered;

	private:
		void Trigger(const GE::Collision::Collider& other, GE::Collision::Detection::CollidedType collidedType);
	};
}