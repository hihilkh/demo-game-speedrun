#include "Task_Player.h"
#include "Utils/Log.h"
#include "Game/Task_GameCamera.h"
#include "Game/Task_Map.h"
#include "Game/GameReference.h"
#include "Game/GameStatus.h"
#include "BasicPlayerAction.h"

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
		ObjectBaseWithResource<Object, Resource>(defGroupName, defName),
		CharaBase(ML::Box2D(-16, -16, 32, 32)),
		isInitialized(false),
		speed(5)
	{
		// TODO : Better way to control priority?
		render2D_Priority[1] = 0.5f;
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
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		ML::Box2D draw = hitBase.OffsetCopy(transform->pos);
		ML::Box2D src(0, 0, 32, 32);

		draw.Offset(camera->GetCameraOffset());
		this->res->img->Draw(draw, src);
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