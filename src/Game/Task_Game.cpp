//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Game.h"
//#include "Ending/Task_Ending.h"
#include "Map/Task_Map.h"
#include "Task_GameCamera.h"
#include "GameEvent.h"
#include "GameStatus.h"
#include "Chara/Player/Task_Player.h"
#include "Task/TaskConstant.h"
#include "Font/Font.h"
#include "SceneTransition/Task_SceneTransition.h"

namespace Game
{
#pragma region Object

	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_Game),
		timer()
	{
		gameEnded.AddListener(this, &Object::GameEndedEventHandler);

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
			//Ending::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
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