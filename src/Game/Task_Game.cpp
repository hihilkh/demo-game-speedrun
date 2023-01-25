//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Game.h"
#include "Ending/Task_Ending.h"
#include "Map/Task_Map.h"
#include "Task_GameCamera.h"
#include "Chara/Player/Task_Player.h"
#include "GameReference.h"
#include "GameStatus.h"
#include "Utils/Log.h"
#include "Task/TaskConstant.h"
#include "GameEvent.h"

namespace Game
{
#pragma region Object

	Object::Object() : ObjectBase<Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_Game)
	{
		gameStatus = make_shared<GameStatus>();
		GameReference::gameStatus = gameStatus;

		// タスクの生成
		// 生成の順番も重要だ。UpDate()の順番につながるから。
		Player::Object::SP player = Player::Object::Create(true);
		Camera::Object::SP camera = Camera::Object::Create(true);
		camera->SetTarget(player->transform);
		Map::Object::SP map = Map::Object::Create(true);

		GameReference::player = player;
		GameReference::gameCamera = camera;
		GameReference::map = map;

		Game::gameEnded.AddListener(this, &Object::GameEndedEventHandler);

		gameReady.Invoke();
	}

	Object::~Object()
	{
		Game::gameEnded.RemoveListeners(this);

		//★データ＆タスク解放
		ge->KillAll_G(TaskConstant::TaskGroupName_Game);
		ge->KillAll_G(TaskConstant::TaskGroupName_Map);
		ge->KillAll_G(TaskConstant::TaskGroupName_Chara);

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
			Ending::Object::SP nextTask = Ending::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		//XI::VGamePad input = ge->in1->GetState();

		//if (input.ST.down) {
		//	this->Kill();
		//}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
	}

	void Object::GameEndedEventHandler()
	{
		Print("ゲームクリア");
	}

#pragma endregion
}