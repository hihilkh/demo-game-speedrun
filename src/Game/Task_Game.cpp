//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Game.h"
#include "Ending/Task_Ending.h"
#include "Map/Task_Map.h"
#include "Task_GameCamera.h"
#include "GameEvent.h"
#include "GameStatus.h"
#include "Chara/Player/Task_Player.h"
#include "Task/TaskConstant.h"
#include "Utils/Time/DelayTrigger.h"
#include "Common/Font.h"
#include "SceneTransition/Task_SceneTransition.h"
#include "Profiling/Profiler.h"

namespace Game
{
#pragma region Object
	bool Object::HasPerformedZoom = false;

	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_Game),
		timer(),
		remainingCountdown(-1)
	{
		GameStatus::CurrentGameState = GameState::Initialize;
		GameStatus::FrameCount = 0;

		render2D_Priority[1] = 0.1f;

		// タスクの生成
		// 生成の順番も重要だ。UpDate()の順番につながるから。
		Player::Object::SP player = Player::Object::Create(true);
		Camera::Object::SP camera = Camera::Object::Create(true);
		camera->SetTarget(player->transform);
		Map::Object::SP map = Map::Object::Create(true);

		gameEnded.AddListener(this, &Object::GameEndedEventHandler);
		mainTaskLoaded.Invoke();

		auto countdown = [this]() {
			this->StartCountdown(3);
		};

		auto performZoom = [this, player, camera, map, countdown]() {
			const ML::Vec2& playerPos = player->transform->pos;
			camera->PerformZoom(ML::Point(playerPos.x, playerPos.y), map->GetGoalPos(), countdown);
		};

		if (HasPerformedZoom) {
			SceneTransition::Fade(false, countdown);
		}
		else {
			HasPerformedZoom = true;
			SceneTransition::Fade(false, performZoom);
		}
	}

	Object::~Object()
	{
		gameEnded.RemoveListeners(this);

		//★データ＆タスク解放
		ge->KillAll_G(TaskConstant::TaskGroupName_Game);
		ge->KillAll_G(TaskConstant::TaskGroupName_Map);
		ge->KillAll_G(TaskConstant::TaskGroupName_Chara);
		ge->KillAll_G(TaskConstant::TaskGroupName_ParticleSystem);

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			GameStatus::ClearGameTimeMillisecond = timer.GetCurrentCountMillisecond();
			//★引き継ぎタスクの生成
			Ending::Object::Create(true);
			DEBUG_PROFILING_SET_SCENE("Ending");
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		++GameStatus::FrameCount;

		XI::VGamePad input = ge->in1->GetState();

#ifdef _DEBUG

		if (input.B1.down) {
			GoToEndingScene();
		}

#endif // _DEBUG

	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Color textColor = ML::Color(1.0f, 0.0f, 0.0f, 0.0f);
		ML::Color frameColor = ML::Color(1.0f, 1.0f, 1.0f, 1.0f);

		// タイマー
		ML::Box2D timerDrawBox = ML::Box2D(0, 0, ge->screenWidth, Font::smallDefaultFontSize);
		string timerText = format("{0:.3f}s", timer.GetCurrentCountMillisecond() / 1000.0f);
		Font::smallDefaultFont->DrawF(timerDrawBox, timerText, DG::Font::x4, textColor, frameColor, DT_RIGHT);

		// カウントダウン
		if (remainingCountdown < 0) {
			return;
		}

		ML::Box2D countdownDrawBox = ML::Box2D(0, 0, ge->screenWidth, ge->screenHeight);
		string countdownText = remainingCountdown == 0 ? "スタート" : to_string(remainingCountdown);		// TODO : ローカライズファイルを用意する
		Font::largeDefaultFont->DrawF(countdownDrawBox, countdownText, DG::Font::x4, textColor, frameColor, DT_CENTER | DT_VCENTER);
	}

	void Object::StartCountdown(int second)
	{
		remainingCountdown = second + 1;	// CountdownEventHandlerの中でまず--remainingCountdownをするので
		CountdownEventHandler();
	}

	void Object::CountdownEventHandler()
	{
		countdownDelayTrigger.reset();
		--remainingCountdown;
		if (remainingCountdown >= 0) {
			countdownDelayTrigger = make_unique<Time::DelayTrigger>(1000, make_unique<MemberFunction<Object>>(this, &Object::CountdownEventHandler));
		}
		else {
			StartGame();
		}
	}

	void Object::StartGame()
	{
		GameStatus::CurrentGameState = GameState::Started;
		timer.Start();
		gameStarted.Invoke();
	}

	void Object::GameEndedEventHandler()
	{
		timer.Pause();
		GameStatus::CurrentGameState = GameState::Ended;
		GoToEndingScene();
	}

	void Object::GoToEndingScene()
	{
		GameStatus::ClearGameTimeMillisecond = timer.GetCurrentCountMillisecond();
		SceneTransition::Fade(true, [this]() { this->Kill(); });
	}

#pragma endregion
}