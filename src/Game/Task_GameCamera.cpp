﻿#include "Task_GameCamera.h"

namespace GameCamera
{

#pragma region Object

	Object::Object() : ObjectBase<Object>(defGroupName, defName), visibleRange(ML::Box2D(0, 0, 480, 270)), currentCameraOffset(ML::Point())
	{
		targetOffset = ML::Point{ -visibleRange.w / 2, -visibleRange.h / 2 };

		UpdateCameraOffset();
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		if (Transform::SP sp = target.lock()) {
			UpdateTarget(sp->pos);
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

	void Object::SetTarget(Transform::SP transform)
	{
		target = transform;
		UpdateTarget(transform->pos);
	}

	void Object::UpdateTarget(const ML::Vec2& pos)
	{
		int newX = int(pos.x) + targetOffset.x;
		int newY = int(pos.y) + targetOffset.y;

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