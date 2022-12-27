#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"
#include "CharaBase.h"
#include "Task_GameCamera.h"

namespace Player
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const string defGroupName(TaskConstant::TaskGroupName_Chara);		//�O���[�v��
	const string defName(TaskConstant::TaskName_Player);				//�^�X�N��

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

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//�u���s�v�P�t���[�����ɍs������
		void Render2D_AF() override;	//�u2D�`��v�P�t���[�����ɍs������

	private:
		GameCamera::Object::SP camera;
		XI::GamePad::SP  controller;

		bool isInitialized;

	public:
		void Initizalize(GameCamera::Object::SP camera, Map::Object::SP map, const ML::Vec2& pos);

	};
}