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

namespace Game
{
#pragma region Resource

	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() : ObjectBase<Object, Resource>(defGroupName, defName)
	{
		//★タスクの生成
		GameCamera::Object::SP camera = GameCamera::Object::Create(true);
		Reference::gameCamera = camera;
		Map::Object::SP map = Map::Object::Create(true);
		Reference::map = map;
		Player::Object::SP player = Player::Object::Create(true);
		Reference::player = player;

		// TODO : Use event system for the timing to get reference
		map->Initialize(Reference::gameCamera.lock());
		map->Load("./data/Map/map2.txt");

		player->Initizalize(camera, map, ML::Vec2(0, 0));
	}

	Object::~Object()
	{
		// TODO
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