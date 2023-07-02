#include "GE/GEHeader.h"
#include "GoalObject.h"

namespace Map
{
	GoalObject::GoalObject(GameObject& gameObject) :
		MapObject(gameObject, Map::MapObjectType::Goal)
	{
	}

	// TODO : Animation
	// TODO : Trigger
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

		if (isTriggered) {
			return;
		}

		auto playerSP = player.lock();
		if (!playerSP) {
			return;
		}

		if (GetCurrentHitBox().Hit(playerSP->GetCurrentHitBox())) {
			isTriggered = true;
			Game::gameEnded.Invoke();
		}
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