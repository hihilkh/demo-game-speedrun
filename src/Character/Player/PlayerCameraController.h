#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include <functional>
#include "GE/DataType/Vector2.h"

namespace Player
{
	class PlayerCameraController : public Component
	{
	public:
		PlayerCameraController(GameObject& gameObject, GE::Camera2D& camera);

		void PerformZoom(const Vector2& targetWorldPos, std::function<void()> onFinished = nullptr) const;

	private:
		GE::Camera2D& camera;
	};
}
