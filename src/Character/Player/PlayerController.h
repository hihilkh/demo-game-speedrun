#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace Player
{
	class PlayerModel;

	class PlayerController : public Component
	{
	public:
		explicit PlayerController(GameObject& gameObject);

	protected:
		void Awake() override;
		void Update() override;
		void EndOfFrame() override;

	private:
		void Deactivate();
	private:
		PlayerModel* model;
	};
}
