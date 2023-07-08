#include "GE/GEHeader.h"
#include "GoalObject.h"
#include "GE/Collision/Collider.h"

namespace Map
{
	GE::Event<> GoalObject::onGoalReached;

	GoalObject::GoalObject(GameObject& gameObject, GE::Collision::Collider& collider) :
		MapObject(gameObject, Map::MapObjectType::Goal),
		collider(collider),
		isTriggered(false)
	{
	}

	void GoalObject::Start()
	{
		collider.onTriggered.AddListener(&GoalObject::Trigger, *this);
	}

	void GoalObject::PreDestroy()
	{
		collider.onTriggered.RemoveListener(&GoalObject::Trigger, *this);
	}

	void GoalObject::Trigger(const GE::Collision::Collider& other)
	{
		if (isTriggered) {
			return;
		}

		isTriggered = true;
		onGoalReached.Invoke();
	}

	// TODO : Animation
}

/*
	void Object::PostCreate()
	{
		using namespace Animation;

		animator = make_unique<Animator>(
			res->img, initializer_list<AnimationClip>{
			AnimationClip(true, {
				AnimationKey(0,		0	, SIZE, SIZE, 10),
				AnimationKey(SIZE,	0	, SIZE, SIZE, 20),
				AnimationKey(0,		SIZE, SIZE, SIZE, 30),
				AnimationKey(SIZE,	SIZE, SIZE, SIZE, 40), })
			}
		);
	}

		void Object::UpDate()
	{
		animator->UpDate();
	}

	void Object::Render2D_AF()
	{
		auto cameraSP = camera.lock();
		if (!cameraSP) {
			return;
		}

		// TODO : カメラに映っていない時に描画しないように
		const ML::Point& cameraOffset = cameraSP->GetCameraOffset();
		ML::Box2D draw = renderBase.OffsetCopy(cameraOffset);
		draw.Offset(pos);
		animator->Render(draw);

		//RenderColliderVisual(GetCurrentHitBox().OffsetCopy(cameraOffset));
	}

*/