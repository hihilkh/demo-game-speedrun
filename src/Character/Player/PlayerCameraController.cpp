#include "GE/GEHeader.h"
#include "PlayerCameraController.h"

#include "Transform/PositionMovement.h"
#include "GE/Utils/Easing.h"

namespace Player
{
	namespace
	{
		const float performZoomMovePeriod = 2.0f;
		const float performZoomFocusTargetTime = 1.0f;
		const GE::Easing::Type performZoomEasingType = GE::Easing::Type::InOutSine;
	}

	PlayerCameraController::PlayerCameraController(GameObject& gameObject, GE::Camera2D& camera) :
		Component(gameObject),
		camera(camera)
	{
	}

	void PlayerCameraController::PerformZoom(const GameObject& target, std::function<void()> onFinished) const
	{
		auto positionMovement = camera.gameObject.GetComponent<TransformUtils::PositionMovement>();
		if (positionMovement == nullptr) {
			positionMovement = &camera.gameObject.AddComponent<TransformUtils::PositionMovement>();
		}

		positionMovement->StartMoving(
			camera.GetTransform().GetWorldPos(),
			target.GetTransform().GetWorldPos(),
			false,
			performZoomMovePeriod,
			performZoomEasingType,
			onFinished,
			true,
			performZoomFocusTargetTime
		);
	}
}

