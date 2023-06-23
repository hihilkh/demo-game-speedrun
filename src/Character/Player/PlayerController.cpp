#include "GE/GEHeader.h"
#include "PlayerController.h"
#include "PlayerModel.h"
#include "GE/Input/InputSystem.h"
#include "PlayerConfig.h"

namespace Player
{
	PlayerController::PlayerController(GameObject& gameObject) :
		Component(gameObject),
		model(nullptr)
	{
	}

	void PlayerController::Awake()
	{
		model = gameObject.GetComponent<PlayerModel>();
		if (model == nullptr) {
			Deactivate();
		}
	}

	void PlayerController::Update()
	{
		// TODO : 仮処理
		Vector2 moveDirection(0.0f, 0.0f);
		if (GE::Input::GetKeyOn(GE::Input::Key::up)) {
			moveDirection.y += 1;
		}
		if (GE::Input::GetKeyOn(GE::Input::Key::down)) {
			moveDirection.y -= 1;
		}
		if (GE::Input::GetKeyOn(GE::Input::Key::left)) {
			moveDirection.x -= 1;
		}
		if (GE::Input::GetKeyOn(GE::Input::Key::right)) {
			moveDirection.x += 1;
		}
		moveDirection.Normalize();

		model->Move(moveDirection, walkSpeed);
	}

	void PlayerController::EndOfFrame()
	{
		if (!model->IsValid()) {
			model = nullptr;
			Deactivate();
		}
	}

	void PlayerController::Deactivate()
	{
		DEBUG_LOG_WARNING("PlayerModelがnullptrになる。PlayerControllerを無効になる。");
		SetEnable(false);
	}
}