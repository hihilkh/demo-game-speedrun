#pragma once

#include "GE/Core/Component.h"
#include "GE/Core/Event.h"

namespace GE::Physics
{
	class Collider : public Component
	{
	public:
		Event<const Collider&> onCollided;
		Event<const Collider&> onTriggered;

	public:
		Collider(GameObject& gameObject, bool isTrigger);
		virtual ~Collider() = default;

		bool GetIsTrigger() const { return isTrigger; }
		void SetIsTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		bool isTrigger;
	};
}
