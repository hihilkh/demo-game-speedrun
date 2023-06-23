#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace Player
{
	class PlayerModel : public Component
	{
	public:
		explicit PlayerModel(GameObject& gameObject);

	public:
		void Move(const Vector2& direction, float speed);

	protected:
		void Start() override;
	};
}
