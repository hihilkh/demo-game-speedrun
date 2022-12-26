//-------------------------------------------------------------------
//�Q�[���{��
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
		//���^�X�N�̐���
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
		//���f�[�^���^�X�N���
		ge->KillAll_G(TaskConstant::TaskGroupName_Game);
		ge->KillAll_G(TaskConstant::TaskGroupName_Map);
		ge->KillAll_G(TaskConstant::TaskGroupName_Chara);

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������p���^�X�N�̐���
			Ending::Object::SP nextTask = Ending::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//�u�X�V�v�P�t���[�����ɍs������
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();
		if (inp.ST.down) {
			//���g�ɏ��ŗv��
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//�u�Q�c�`��v�P�t���[�����ɍs������
	void  Object::Render2D_AF()
	{
	}

#pragma endregion
}