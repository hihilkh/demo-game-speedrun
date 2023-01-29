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
#include "Utils/Log.h"
#include "Utils/Time/DelayTrigger.h"

namespace Game
{
#pragma region Resource
	Resource::Resource() : 
		smallFontSize(24),
		largeFontSize(40)
	{
		// TODO : 処理は重そうだ
		smallFont = DG::Font::Create(ResourceConstant::DefaultFontName, smallFontSize / 2, smallFontSize);
		largeFont = DG::Font::Create(ResourceConstant::DefaultFontName, largeFontSize / 2, largeFontSize);
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() : 
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_Game),
		timer(),
		remainingCountdown(3)
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
		gameReady.Invoke();

		StartCountdown();
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
			//★引き継ぎタスクの生成
			Ending::Object::SP nextTask = Ending::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		++GameStatus::FrameCount;

		XI::VGamePad input = ge->in1->GetState();

		if (input.B1.down) {
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Color textColor = ML::Color(1.0f, 0.0f, 0.0f, 0.0f);
		ML::Color frameColor = ML::Color(1.0f, 1.0f, 1.0f, 1.0f);

		// タイマー
		ML::Box2D timerDrawBox = ML::Box2D(0, 0, ge->screenWidth, res->smallFontSize);
		string timerText = format("{0:.3f}s", timer.GetCurrentCountMillisecond() / 1000.0f);
		res->smallFont->DrawF(timerDrawBox, timerText, DG::Font::x4, textColor, frameColor, DT_RIGHT);

		// カウントダウン
		if (remainingCountdown < 0) {
			return;
		}

		ML::Box2D countdownDrawBox = ML::Box2D(0, 0, ge->screenWidth, ge->screenHeight);
		string countdownText = remainingCountdown == 0 ? "スタート" : to_string(remainingCountdown);		// TODO : ローカライズファイルを用意する
		res->largeFont->DrawF(countdownDrawBox, countdownText, DG::Font::x4, textColor, frameColor, DT_CENTER | DT_VCENTER);
	}

	void Object::StartCountdown()
	{
		++remainingCountdown;	// CountdownEventHandlerの中でまず--remainingCountdownをするので
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
		GameStatus::CurrentGameState = GameState::Ended;
		Print("ゲームクリア");
	}

#pragma endregion
}