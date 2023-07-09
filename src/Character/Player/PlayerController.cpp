#include "GE/GEHeader.h"
#include "PlayerController.h"
#include "PlayerModel.h"
#include "GE/Input/InputSystem.h"
#include "PlayerConfig.h"
#include "GameScene/GameSceneDirector.h"

namespace Player
{
	PlayerController::PlayerController(GameObject& gameObject, PlayerModel& model) :
		Component(gameObject),
		model(model)
	{
	}

	void PlayerController::Update()
	{
		if (!CanControl()) {
			return;
		}

		// 走る
		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			model.StartRunning();
			return;
		} else if (GE::Input::GetKeyUp(GE::Input::Key::x)) {
			model.StopRunning();
			return;
		}

		// 歩く
		Vector2 dirVector = Vector2::zero;

		if (GE::Input::GetKeyOn(GE::Input::Key::left))	{ dirVector += Vector2::left; }
		if (GE::Input::GetKeyOn(GE::Input::Key::right)) { dirVector += Vector2::right; }
		if (GE::Input::GetKeyOn(GE::Input::Key::up))	{ dirVector += Vector2::up; }
		if (GE::Input::GetKeyOn(GE::Input::Key::down))	{ dirVector += Vector2::down; }

		model.Move(dirVector);
	}

	bool PlayerController::CanControl() const
	{
		return	GameScene::Director::GetGameState() == GameScene::GameState::Started &&
				model.CanControl();
	}
}