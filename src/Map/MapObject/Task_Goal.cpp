#include "Task_Goal.h"
#include "Task/TaskConstant.h"
#include "Game/Task_GameCamera.h"
#include "MyPG.h"
#include "Animation/Animator.h"

namespace Goal
{
#pragma region Resource

	Resource::Resource()
	{
		img = DG::Image::Create(GetImagePath(ResourceConstant::GoalImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

#define SIZE ResourceConstant::MapObjectSize

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_MapObject, TaskConstant::TaskName_Goal, true),
		pos(ML::Point()),
		hitBase(ML::Box2D()),	// TODO
		renderBase(ML::Box2D(0, -SIZE / 3, SIZE, SIZE))
	{
		render2D_Priority[1] = 0.8f;

		camera = ge->GetTask<Game::Camera::Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera);
	}

	void Object::PostCreate()
	{
		using namespace Animation;

		animator = make_unique<Animator>(
			this->res->img, initializer_list<AnimationClip>{
			AnimationClip(true, {
				AnimationKey(0,		0	, SIZE, SIZE, 10),
				AnimationKey(SIZE,	0	, SIZE, SIZE, 20),
				AnimationKey(0,		SIZE, SIZE, SIZE, 30),
				AnimationKey(SIZE,	SIZE, SIZE, SIZE, 40), })
			}
		);
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		animator->UpDate();
	}

	void Object::Render2D_AF()
	{
		if (!camera) {
			return;
		}

		// TODO : Check is inside camera
		const ML::Box2D& visibleRange = camera->GetVisibleRange();
		ML::Box2D draw = renderBase.OffsetCopy(-visibleRange.x + pos.x, -visibleRange.y + pos.y);
		animator->Render(draw);
	}

	void Object::Init(int posX, int posY)
	{
		this->pos.x = posX;
		this->pos.y = posY;
	}

#pragma endregion
}