#include "Task_Player.h"


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

	Object::Object() : ObjectBase<Object, Resource>(defGroupName, defName, true), CharaBase(ML::Box2D(-16, -16, 32, 32))
	{
		// TODO : Better way to control priority?
		render2D_Priority[1] = 0.5f;
		// TODO : Plater Controller?
		controller = ge->in1;
	}

	Object::~Object()
	{
		// TODO : is reset needed?
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


	void Object::Initizalize(GameCamera::Object::SP camera, Map::Object::SP map, const ML::Vec2& pos)
	{
		isInitialized = true;
		this->camera = camera;
		this->map = map;
		this->pos = pos;

	}

#pragma endregion
}