#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include <functional>

namespace Player
{
	class PlayerCameraController : public Component
	{
	public:
		PlayerCameraController(GameObject& gameObject, GE::Camera2D& camera);

		void PerformZoom(const GameObject& target, std::function<void()> onFinished = nullptr) const;

	private:
		GE::Camera2D& camera;
	};
}
