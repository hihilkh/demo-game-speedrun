#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "Camera/CameraManagement.h"
#include "Utils/FollowPos.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void PlayerModel::Start()
	{
		GameObject* mainCamera = GE::FindGameObject(Camera::mainCameraName);
		if (mainCamera == nullptr) {
			DEBUG_LOG_WARNING("mainCameraを見つけられない。Playerが追跡できない。");
		} else {
			auto followPos = mainCamera->GetComponent<Utils::FollowPos>();
			if (followPos == nullptr) {
				followPos = &mainCamera->AddComponent<Utils::FollowPos>();
			}

			followPos->SetTarget(GetTransform());
		}
	}

	void PlayerModel::Move(const Vector2& direction, float speed)
	{
		// TODO : 仮処理
		GetTransform().pos.x += direction.x * speed;
		GetTransform().pos.y += direction.y * speed;
	}
}