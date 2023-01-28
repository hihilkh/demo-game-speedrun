#include "Task_GameCamera.h"
#include "Task/TaskConstant.h"

namespace Game::Camera
{

#pragma region Object

	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera, true), 
		visibleRange(ML::Box2D(0, 0, 480, 270)), 
		currentCameraOffset(ML::Point())
	{
		targetOffset = ML::Point{ -visibleRange.w / 2, -visibleRange.h / 2 };

		UpdateCameraOffset();
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		UpdateTarget();
	}

	void Object::Render2D_AF()
	{
	}

	const ML::Box2D& Object::GetVisibleRange() const
	{
		return visibleRange;
	}

	const ML::Point& Object::GetCameraOffset() const
	{
		return currentCameraOffset;
	}

	void Object::SetTarget(Transform::WP transform)
	{
		target = transform;
		UpdateTarget();
	}

	void Object::UpdateTarget()
	{
		Transform::SP sp = target.lock();
		if (!sp) {
			return;
		}

		int newX = int(sp->pos.x) + targetOffset.x;
		int newY = int(sp->pos.y) + targetOffset.y;

		visibleRange.x = newX;
		visibleRange.y = newY;

		UpdateCameraOffset();
	}

	void Object::UpdateCameraOffset()
	{
		currentCameraOffset.x = -visibleRange.x;
		currentCameraOffset.y = -visibleRange.y;
	}

#pragma endregion
}