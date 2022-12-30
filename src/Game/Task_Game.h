﻿#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

#pragma region 前方宣言

namespace Game { class GameStatus; }

#pragma endregion

namespace Game
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Game);		//グループ名
	const string defName(TaskConstant::TaskName_Game);					//タスク名

	class Object : public ObjectBase<Object>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		shared_ptr<GameStatus> gameStatus;
	};
}