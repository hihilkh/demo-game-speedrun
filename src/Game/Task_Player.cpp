#include "Task_Player.h"
#include "GameReference.h"
#include "Utils/Log.h"
#include "Task_GameCamera.h"
#include "Task_Map.h"
#include "GameReference.h"
#include "GameStatus.h"

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
		speed(5),
		controller(ge->in1)
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

		ML::Vec2 targetMove = ML::Vec2(0, 0);

		auto inp = controller->GetState();
		if (inp.LStick.BL.on) { targetMove.x -= speed; direction = Direction::Left; }
		if (inp.LStick.BR.on) { targetMove.x += speed; direction = Direction::Right; }
		if (inp.LStick.BU.on) { targetMove.y -= speed; }
		if (inp.LStick.BD.on) { targetMove.y += speed; }

		AdjustMoveWithMap(targetMove);
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
		isInitialized = true;
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
	}

#pragma endregion
}