#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Chara/CharaBase.h"
#include "PlayerMode.h"
#include "PlayerState.h"

#pragma region 前方宣言

namespace GameCamera { class Object; }

#pragma endregion

namespace Player
{
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

	public:
		DG::Image::SP img;
	};

	class Object : public ObjectBaseWithResource<Object, Resource>, public Chara::CharaBase
	{
		friend ObjectBase<Object>;

#pragma region PlayerAction の friend になる

		friend class PlayerActionBase;
		friend class BasicPlayerAction;
		friend class AttackPlayerAction;
		friend class RunPlayerAction;

#pragma endregion

	private:
		Object();

	protected:
		void PostCreate() override;

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		shared_ptr<GameCamera::Object> camera;

		bool isInitialized;
		bool canControl;
		float currentMovementSpeed;		// Inputによっての速度。実際の速度ではない。
		float currentHeight;
		PlayerState state;
		unique_ptr<class PlayerActionBase> playerAction;		// TODO : Or change to the concept of controller?
		unique_ptr<class PlayerAnimator> animator;

		int fallbackCounter;

	private:
		void GameReadyEventHandler();

		void UpdatePlayerAction(PlayerMode playerMode);
		void Fallback();
		void UpdateFallback();

	protected:

#pragma region 移動の流れ

		/// <returns>targetMove</returns>
		ML::Vec2 PreMove() override;
		void CollideWithMap() override;
		void PostMove() override;

#pragma endregion

	public:
		PlayerState GetState() const { return state; }
		bool CheckIsInCrashSpeed() const;
	};
}