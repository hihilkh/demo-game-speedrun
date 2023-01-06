#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Task/TaskConstant.h"
#include "Chara/CharaBase.h"
#include "PlayerMode.h"
#include "PlayerState.h"

#pragma region 前方宣言

namespace GameCamera { class Object; }

#pragma endregion

namespace Player
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Chara);		//グループ名
	const string defName(TaskConstant::TaskName_Player);				//タスク名

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

	class Object : public ObjectBaseWithResource<Object, Resource>, public CharaBase
	{
		friend ObjectBase<Object>;

#pragma region PlayerAction の friend になる

		friend class PlayerActionBase;
		friend class BasicPlayerAction;
		friend class AttackPlayerAction;

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
		float speed;
		PlayerState state;
		unique_ptr<class PlayerActionBase> playerAction;
		unique_ptr<class PlayerAnimator> animator;

	private:
		void UpdatePlayerAction(PlayerMode playerMode);

	public:
		void Initizalize();
		PlayerState GetState() const { return state; }
	};
}