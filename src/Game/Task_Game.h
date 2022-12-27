#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//�Q�[���{��
//-------------------------------------------------------------------
#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

namespace Game
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const string defGroupName(TaskConstant::TaskGroupName_Game);		//�O���[�v��
	const string defName(TaskConstant::TaskName_Game);					//�^�X�N��

	class Object : public ObjectBase<Object>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//�u���s�v�P�t���[�����ɍs������
		void Render2D_AF() override;	//�u2D�`��v�P�t���[�����ɍs������
	};
}