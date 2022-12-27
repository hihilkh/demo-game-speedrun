#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

namespace GameCamera
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const string defGroupName(TaskConstant::TaskGroupName_Game);		//�O���[�v��
	const string defName(TaskConstant::TaskName_GameCamera);			//�^�X�N��

	class Object : public ObjectBase<Object>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//�u���s�v�P�t���[�����ɍs������
		void Render2D_AF() override;	//�u2D�`��v�P�t���[�����ɍs������

	private:
		ML::Box2D visibleRange;
		int targetOffsetX;
		int targetOffsetY;
		ML::Point currentCameraOffset;

	private:
		void UpdateCameraOffset();

	public:
		// TODO : Study about getter overload
		ML::Box2D GetVisibleRange();
		const ML::Point& GetCameraOffset() const;

		void UpdateTarget(const ML::Vec2& pos);
	};
}