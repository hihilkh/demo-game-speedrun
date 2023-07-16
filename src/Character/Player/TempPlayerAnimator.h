#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace Player
{
	class PlayerModel;

	class TempPlayerAnimator : public Component
	{
	public:
		TempPlayerAnimator(GameObject& gameObject, PlayerModel& model, Image& image);

	public:

	protected:
		void LateUpdate() override;

	private:
		PlayerModel& model;
		Image& image;
	};
}
