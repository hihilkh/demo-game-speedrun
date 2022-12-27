//-------------------------------------------------------------------
//�G���f�B���O
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Ending.h"
#include "Title/Task_Title.h"

namespace Ending
{
#pragma region Resource

	Resource::Resource()
	{
		this->img = DG::Image::Create(GetImagePath(ResourceConstant::EndingImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() : ObjectBaseWithResource<Object, Resource>(defGroupName, defName)
	{
		this->logoPosY = 270;
	}

	Object::~Object()
	{
		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������p���^�X�N�̐���
			Title::Object::SP nextTask = Title::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//�u�X�V�v�P�t���[�����ɍs������
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		this->logoPosY -= 9;
		if (this->logoPosY <= 0) {
			this->logoPosY = 0;
		}

		if (this->logoPosY == 0) {
			if (inp.ST.down) {
				//���g�ɏ��ŗv��
				this->Kill();
			}
		}
	}
	//-------------------------------------------------------------------
	//�u�Q�c�`��v�P�t���[�����ɍs������
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, 480, 270);
		ML::Box2D  src(0, 0, 240, 135);

		draw.Offset(0, this->logoPosY);
		this->res->img->Draw(draw, src);
	}

#pragma endregion
}