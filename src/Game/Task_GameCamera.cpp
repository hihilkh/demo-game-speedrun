#include "Task_GameCamera.h"

namespace GameCamera
{

#pragma region Object

	Object::Object() : ObjectBase<Object>(defGroupName, defName), visibleRange(ML::Box2D(0, 0, 480, 270)), currentCameraOffset(ML::Point())
	{
		targetOffsetX = -visibleRange.w / 2;
		targetOffsetY = -visibleRange.h / 2;

		UpdateCameraOffset();
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		auto inp = ge->in1->GetState();
		if (inp.ST.down) {
			//自身に消滅要請
			this->Kill();
		}
	}

	void Object::Render2D_AF()
	{
	}

	ML::Box2D Object::GetVisibleRange()
	{
		return visibleRange;
	}

	const ML::Point& Object::GetCameraOffset() const
	{
		return currentCameraOffset;
	}

	void Object::UpdateTarget(const ML::Vec2& pos)
	{
		int newX = int(pos.x) + targetOffsetX;
		int newY = int(pos.y) + targetOffsetY;

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