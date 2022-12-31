//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Game.h"
#include "Ending/Task_Ending.h"
#include "Task_Map.h"
#include "Task_GameCamera.h"
#include "Task_Player.h"
#include "GameReference.h"
#include "GameStatus.h"

namespace Game
{

#pragma region Object

	Object::Object() : ObjectBase<Object>(defGroupName, defName)
	{
		gameStatus = make_shared<GameStatus>(GameStatus());
		GameReference::gameStatus = gameStatus;

		// タスクの生成
		// 生成の順番も重要だ。UpDate()の順番につながるから。
		Player::Object::SP player = Player::Object::Create(true);
		GameCamera::Object::SP camera = GameCamera::Object::Create(true);
		camera->SetTarget(player->transform);
		Map::Object::SP map = Map::Object::Create(true);

		GameReference::player = player;
		GameReference::gameCamera = camera;
		GameReference::map = map;

		// TODO : Use event system for the timing to get reference
		player->Initizalize();
		map->Initialize();
	}

	Object::~Object()
	{
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
		auto inp = ge->in1->GetState();
		if (inp.ST.down) {
			//自身に消滅要請
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
	}

#pragma endregion
}