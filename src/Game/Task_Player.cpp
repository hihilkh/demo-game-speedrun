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

	Object::Object() : ObjectBaseWithResource<Object, Resource>(defGroupName, defName, true), CharaBase(ML::Box2D(-16, -16, 32, 32))
	{
		// TODO : Better way to control priority?
		render2D_Priority[1] = 0.5f;
		// TODO : Player Controller?
		controller = ge->in1;
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		if (!isInitialized) {
			return;
		}

		ML::Vec2 est(0, 0);

		auto inp = controller->GetState();
		if (inp.LStick.BL.on) { est.x -= 3; direction = Direction::Left; }
		if (inp.LStick.BR.on) { est.x += 3; direction = Direction::Right; }
		if (inp.LStick.BU.on) { est.y -= 3; }
		if (inp.LStick.BD.on) { est.y += 3; }

		AdjustMoveWithMap(est);
		camera->UpdateTarget(pos);
		map->AdjustCameraPos();
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		ML::Box2D draw = this->hitBase.OffsetCopy(this->pos);
		ML::Box2D src(0, 0, 32, 32);

		draw.Offset(camera->GetCameraOffset());
		this->res->img->Draw(draw, src);
	}


	void Object::Initizalize()
	{
		isInitialized = true;
		this->camera = Game::GameReference::GetGameCamera();
		this->map = Game::GameReference::GetMap();

		Game::GameStatus::SP gameStatus = Game::GameReference::GetGameStatus();
		if (gameStatus) {
			this->pos = gameStatus->GetInitialPos();
		}
		else {
			PrintWarning("GameStatusが取れない。posをデフォルトになる。");
			this->pos = ML::Vec2();
		}
	}

#pragma endregion
}