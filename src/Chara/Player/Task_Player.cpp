#include "Task_Player.h"
#include "Utils/Log.h"
#include "Game/Task_GameCamera.h"
#include "Game/Task_Map.h"
#include "Game/GameReference.h"
#include "Game/GameStatus.h"
#include "BasicPlayerAction.h"
#include "PlayerConstant.h"
#include "PlayerAnimator.h"
#include "Task/TaskConstant.h"

namespace Player
{
#pragma region Resource

	Resource::Resource()
	{
		img = DG::Image::Create(GetImagePath(ResourceConstant::PlayerImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() : 
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Chara, TaskConstant::TaskName_Player),
		CharaBase(ML::Box2D(-PlayerConstant::HitBaseWidth / 2, -PlayerConstant::HitBaseHeight / 2, PlayerConstant::HitBaseWidth, PlayerConstant::HitBaseHeight)),
		isInitialized(false),
		speed(5),
		state(PlayerState::Idle)
	{
		// TODO : Better way to control priority?
		render2D_Priority[1] = 0.5f;
	}

	void Object::PostCreate()
	{
		SP sharedPtr = dynamic_pointer_cast<Object>(this->me.lock());
		animator = make_unique<PlayerAnimator>(sharedPtr, this->res);
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		if (!isInitialized) {
			return;
		}

#if _DEBUG
		// バックドア：PlayerActionの切り替え
		auto inp = ge->in1->GetState();
		if (inp.SE.down) {
			switch (playerAction->GetPlayerMode()) {
				case PlayerMode::Basic:	// TODO 
				case PlayerMode::Attack:	// TODO 
				case PlayerMode::Run:	// TODO 
				case PlayerMode::Jump:		UpdatePlayerAction(PlayerMode::Basic);		break;
			}
		}
#endif

		playerAction->UpDate();
		animator->UpDate();
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		animator->Render(hitBase.OffsetCopy(transform->pos), camera->GetCameraOffset());
	}

	void Object::Initizalize()
	{
		UpdatePlayerAction(PlayerMode::Basic);

		camera = Game::GameReference::GetGameCamera();
		map = Game::GameReference::GetMap();

		Game::GameStatus::SP gameStatus = Game::GameReference::GetGameStatus();
		if (gameStatus) {
			transform->pos = gameStatus->GetInitialPos();
		}
		else {
			PrintWarning("GameStatusが取れない。posをデフォルトになる。");
			transform->pos = ML::Vec2();
		}

		isInitialized = true;
	}

	void Object::UpdatePlayerAction(PlayerMode playerMode)
	{
		SP sharedPtr = dynamic_pointer_cast<Object>(this->me.lock());

		switch (playerMode) {
			// TODO : 他のcase
			case PlayerMode::Basic:
			default:
				playerAction = make_unique<BasicPlayerAction>(sharedPtr, ge->in1);
				break;
		}

		Print((string)"今のPlayerAction：" + typeid(*playerAction).name());
	}

#pragma endregion
}