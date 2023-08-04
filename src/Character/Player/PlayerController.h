#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace Player
{
	class PlayerModel;

	class PlayerController : public Component
	{
	public:
		PlayerController(GameObject& gameObject, PlayerModel& model);

	protected:
		void Update() override;

	private:
		PlayerModel& model;

	private:
		bool CanControl() const;

	};
}
