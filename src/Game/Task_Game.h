﻿#pragma once
//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Event/Event.tpp"
#include "Utils/Timer.h"

#pragma region 前方宣言

namespace Utils { class DelayTrigger; }

#pragma endregion

namespace Game
{
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
		static bool HasPerformedZoom;

		Utils::Timer timer;
		int remainingCountdown;
		unique_ptr<Utils::DelayTrigger> countdownDelayTrigger;

	private:
		void StartCountdown(int second);
		void CountdownEventHandler();
		void StartGame();
		void GameEndedEventHandler();

		void GoToEndingScene();
	};
}