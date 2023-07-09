#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace GE::Render
{
	class Image;
}

namespace Player
{
	class PlayerModel;

	class TempPlayerAnimator : public Component
	{
	public:
		TempPlayerAnimator(GameObject& gameObject, PlayerModel& model, GE::Render::Image& image);

	public:

	protected:
		void LateUpdate() override;

	private:
		PlayerModel& model;
		GE::Render::Image& image;
	};
}
