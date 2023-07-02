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

	// TODO : 今もしPerformZoomをしているとき、Playerが移動すれば、表示は変になる
	void PlayerCameraController::PerformZoom(const Vector2& targetWorldPos, std::function<void()> onFinished)
	{
		auto positionMovement = camera.gameObject.GetComponent<TransformUtils::PositionMovement>();
		if (positionMovement == nullptr) {
			positionMovement = &camera.gameObject.AddComponent<TransformUtils::PositionMovement>();
		}

		positionMovement->StartMoving(
			camera.GetTransform().GetWorldPos(),
			targetWorldPos,
			false,
			performZoomMovePeriod,
			performZoomEasingType,
			onFinished,
			true,
			performZoomFocusTargetTime
		);
	}
}

