#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//�^�C�g�����
//-------------------------------------------------------------------
#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

namespace Title
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const string defGroupName(TaskConstant::TaskGroupName_Title);		//�O���[�v��
	const string defName(TaskConstant::TaskName_Default);				//�^�X�N��

	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

		DG::Image::SP img;
	};

	class Object : public ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//�u���s�v�P�t���[�����ɍs������
		void Render2D_AF() override;	//�u2D�`��v�P�t���[�����ɍs������

		int logoPosY;		//�^�C�g���摜�X�N���[���p�J�E���^
	};
}