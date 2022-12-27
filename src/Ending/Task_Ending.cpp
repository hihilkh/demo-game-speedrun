//-------------------------------------------------------------------
//エンディング
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
			//★引き継ぎタスクの生成
			Title::Object::SP nextTask = Title::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		this->logoPosY -= 9;
		if (this->logoPosY <= 0) {
			this->logoPosY = 0;
		}

		if (this->logoPosY == 0) {
			if (inp.ST.down) {
				//自身に消滅要請
				this->Kill();
			}
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, 480, 270);
		ML::Box2D  src(0, 0, 240, 135);

		draw.Offset(0, this->logoPosY);
		this->res->img->Draw(draw, src);
	}

#pragma endregion
}