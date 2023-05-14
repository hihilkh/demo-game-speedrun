#include "Task_GameCamera.h"
#include "Task/TaskConstant.h"
#include "GE/Utils/Math.h"

namespace Game::Camera
{

#pragma region Object

#define PerformZoomPhase1 120
#define PerformZoomPhase2 180 // 120 + 60
#define PerformZoomPhase3 300 // 120 + 60 + 120

	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera, true), 
		visibleRange(ML::Box2D(0, 0, 480, 270)), 
		currentCameraOffset(ML::Point()),
		isPerformingZoom(false),
		performZoomFrom(ML::Point()),
		performZoomTo(ML::Point()),
		onFinishedPerformZoom(nullptr),
		currentPerformZoomCount(0)
	{
		targetOffset = ML::Point{ -visibleRange.w / 2, -visibleRange.h / 2 };

		UpdateCameraOffset();
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		if (isPerformingZoom) {
			UpdateZoom();
			return;
		}

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

		UpdateCameraPos(sp->pos.x, sp->pos.y);
	}

	void Object::UpdateCameraPos(int targatX, int targetY)
	{
		visibleRange.x = targatX + targetOffset.x;
		visibleRange.y = targetY + targetOffset.y;

		UpdateCameraOffset();
	}

	void Object::UpdateCameraOffset()
	{
		currentCameraOffset.x = -visibleRange.x;
		currentCameraOffset.y = -visibleRange.y;
	}

	// TODO : UnityのStartCoroutineのようなメソッドを作る
	void Object::PerformZoom(const ML::Point& from, const ML::Point& to, std::function<void()> onFinished)
	{
		isPerformingZoom = true;
		performZoomFrom = from;
		performZoomTo = to;
		onFinishedPerformZoom = onFinished;
		currentPerformZoomCount = 0;
	}

	void Object::UpdateZoom()
	{
		++currentPerformZoomCount;

		float progress;
		if (currentPerformZoomCount <= PerformZoomPhase1) {
			progress = Math::EaseInOutSine(currentPerformZoomCount / (float)PerformZoomPhase1);
		}
		else if (currentPerformZoomCount <= PerformZoomPhase2) {
			// 何もしない
			return;
		}
		else if (currentPerformZoomCount <= PerformZoomPhase3) {
			float t = (PerformZoomPhase3 - currentPerformZoomCount) / (float)(PerformZoomPhase3 - PerformZoomPhase2);
			progress = Math::EaseInOutSine(t);

			if (currentPerformZoomCount == PerformZoomPhase3) {
				isPerformingZoom = false;
				if (onFinishedPerformZoom) {
					onFinishedPerformZoom();
					onFinishedPerformZoom = nullptr;
				}
			}
		}

		UpdateCameraPos(
			std::lerp(performZoomFrom.x, performZoomTo.x, progress),
			std::lerp(performZoomFrom.y, performZoomTo.y, progress));
	}

#pragma endregion
}