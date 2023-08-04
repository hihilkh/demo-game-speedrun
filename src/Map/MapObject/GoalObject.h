#pragma once

#include "MapObject.h"
#include "GE/Core/Event.h"

namespace Map
{
	class GoalObject : public MapObject
	{
	public:
		static GE::Event<> onGoalReached;

	public:
		GoalObject(GameObject& gameObject, Collider& collider);

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		Collider& collider;

		bool isTriggered;

	private:
		void Trigger(const Collider& other, CollidedType collidedType);
	};
}