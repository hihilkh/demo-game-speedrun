﻿#include "Task_Player.h"
#include <numbers>
#include "GE/Debug/Log.h"
#include "Game/Task_GameCamera.h"
#include "Map/Task_Map.h"
#include "Game/GameStatus.h"
#include "BasicPlayerAction.h"
#include "AttackPlayerAction.h"
#include "RunPlayerAction.h"
#include "PlayerConstant.h"
#include "PlayerAnimator.h"
#include "Task/TaskConstant.h"
//#include "Game/GameEvent.h"

namespace Player
{
#pragma region Resource

	Resource::Resource()
	{
		// TODO : 一つの画像になる
		playerImg = DG::Image::Create(GetImagePath(ResourceConstant::PlayerImage));
		shadowImg = DG::Image::Create(GetImagePath(ResourceConstant::PlayerShadowImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Chara, TaskConstant::TaskName_Player, true),
		CharaBase(Constant::HitBase, Constant::RenderBase),
		isInitialized(false),
		canControl(true),
		currentHeight(0),
		state(PlayerState::Idle),
		fallbackCounter(0)
	{
		// TODO : レンダリング順についてより良い方法
		render2D_Priority[1] = 0.5f;

		//Game::mapLoaded.AddListener(this, &Object::MapLoadedEventHandler);
	}

	void Object::PostCreate()
	{
		SP sharedPtr = dynamic_pointer_cast<Object>(this->me.lock());
		animator = make_unique<PlayerAnimator>(sharedPtr, this->res);
	}

	Object::~Object()
	{
		//Game::mapLoaded.RemoveListeners(this);
	}

	void Object::UpDate()
	{
		if (!isInitialized) {
			return;
		}

		if (!canControl) {
			if (state == PlayerState::Fallback) {
				UpdateFallback();
			}
			return;
		}

#ifdef _DEBUG

		// バックドア：PlayerActionの切り替え
		auto inp = ge->in1->GetState();
		if (inp.SE.down) {
			switch (playerAction->GetPlayerMode()) {
				case PlayerMode::Basic:		UpdatePlayerAction(PlayerMode::Attack);		break;
				case PlayerMode::Attack:	UpdatePlayerAction(PlayerMode::Run);		break;
				case PlayerMode::Run:	// TODO 
				case PlayerMode::Jump:		UpdatePlayerAction(PlayerMode::Basic);		break;
			}
		}

#endif // _DEBUG

		UpdateMovement();
	}

	ML::Vec2 Object::PreMove()
	{
		return playerAction->PreMove();
	}

	void Object::CollidedWithMap(const vector<Direction>& collidedDirections)
	{
		playerAction->CollidedWithMap(collidedDirections);

		if (CheckIsInCrashStateAndSpeed()) {
			for (Direction direction : collidedDirections) {
				// 反対方向
				if (CompareDirection(direction, transform->direction) == -1) {
					Fallback();
					return;
				}
			}

		}
	}

	void Object::PostMove()
	{
		animator->UpDate();
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		if (auto cameraSP = camera.lock()) {
			animator->Render(GetCurrentRenderBox(), cameraSP->GetCameraOffset(), (int)currentHeight);
		}
	}

	void Object::MapLoadedEventHandler()
	{
		//UpdatePlayerAction(PlayerMode::Basic);
		UpdatePlayerAction(PlayerMode::Run);

		camera = ge->GetTask<Game::Camera::Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera);
		map = ge->GetTask<Map::Object>(TaskConstant::TaskGroupName_Map, TaskConstant::TaskName_Map);

		transform->pos = Game::GameStatus::PlayerInitialPos;

		isInitialized = true;
	}

	void Object::UpdatePlayerAction(PlayerMode playerMode)
	{
		WP weakPtr = dynamic_pointer_cast<Object>(this->me.lock());

		switch (playerMode) {
			// TODO : 他のcase
			case PlayerMode::Basic:		playerAction = make_unique<BasicPlayerAction>(weakPtr);		break;
			case PlayerMode::Attack:	playerAction = make_unique<AttackPlayerAction>(weakPtr);	break;
			case PlayerMode::Run:		playerAction = make_unique<RunPlayerAction>(weakPtr);		break;
		}

		DEBUG_LOG("今のPlayerAction：" << typeid(*playerAction).name());
	}

	void Object::Fallback()
	{
		DEBUG_LOG("撃退された");
		currentMovementSpeed = 0;
		canControl = false;
		fallbackCounter = 0;
		state = PlayerState::Fallback;
	}

	void Object::UpdateFallback()
	{
		if (fallbackCounter < Constant::FallbackPeriod) {
			++fallbackCounter;

			currentHeight = Constant::FallbackMaxHeight * sin((float)fallbackCounter / Constant::FallbackPeriod * (float)std::numbers::pi);

			ML::Vec2 targetMove = GetDirectionalVector(transform->direction) * (-Constant::FallbackBackSpeed);
			CheckMapCollisionAndMove(targetMove);
		}
		else {
			currentHeight = 0;
			canControl = true;
			state = PlayerState::Idle;
		}
	}

	bool Object::CheckIsInCrashStateAndSpeed() const
	{
		if (state == PlayerState::Running || state == PlayerState::Stopping) {
			DEBUG_LOG("Running/Stopping速度：" << currentMovementSpeed);
			return currentMovementSpeed > Constant::CrashSpeed;
		}

		return false;
	}

#pragma endregion
}