﻿#include "Task_Goal.h"
#include "Task/TaskConstant.h"
#include "Game/Task_GameCamera.h"
#include "MyPG.h"
#include "Animation/Animator.h"
#include "GE/Debug/ColliderVisual.h"
#include "Chara/Player/Task_Player.h"
#include "Game/GameEvent.h"

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

#define SIZE 32

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_MapObject, TaskConstant::TaskName_Goal, true),
		pos(ML::Point()),
		hitBase(ML::Box2D(-6, -12, 12, 24)),
		renderBase(ML::Box2D(-SIZE / 2, -SIZE * 5 / 6, SIZE, SIZE)),
		isTriggered(false)
	{
		render2D_Priority[1] = 0.8f;

		camera = ge->GetTask<Game::Camera::Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera);
		player = ge->GetTask<Player::Object>(TaskConstant::TaskGroupName_Chara, TaskConstant::TaskName_Player);
	}

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

	Object::~Object()
	{
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

		RenderColliderVisual(GetCurrentHitBox().OffsetCopy(cameraOffset));
	}

	void Object::Init(int posX, int posY)
	{
		this->pos.x = posX;
		this->pos.y = posY;
	}

	ML::Box2D Object::GetCurrentHitBox() const
	{
		return hitBase.OffsetCopy(pos);
	}

#pragma endregion
}