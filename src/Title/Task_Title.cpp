//-------------------------------------------------------------------
//タイトル画面
//-------------------------------------------------------------------
#include "Task_Title.h"
#include "Game/Task_Game.h"
#include "Task/TaskConstant.h"
#include "Common/Font.h"

namespace Title
{
#pragma region Resource

	Resource::Resource()
	{
		imgTitle = DG::Image::Create(GetImagePath(ResourceConstant::TitleImage));
		imgArrow = DG::Image::Create(GetImagePath(ResourceConstant::ArrowImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	enum Menu
	{
		Start = 0,
		Quit = 1,
		EnumEnd = 2,
	};

	Object::Object() : 
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Title, TaskConstant::TaskName_Default),
		selectingMenu(Menu::Start)
	{
	}

	Object::~Object()
	{
		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
			Game::Object::SP nextTask = Game::Object::Create(true);
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		if (inp.LStick.BU.down) {
			selectingMenu = max(selectingMenu - 1, 0);
		}
		else if (inp.LStick.BD.down) {
			selectingMenu = min(selectingMenu + 1, Menu::EnumEnd - 1);
		}


		if (inp.B2.down) {
			switch (selectingMenu) {
				case Menu::Start:
					//自身に消滅要請
					this->Kill();
					break;
				case Menu::Quit:
					exit(0);
					break;
			}
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void Object::Render2D_AF()
	{
		// ロゴ
		ML::Box2D logoSrc = ML::Box2D(0, 0, 300, 50);
		ML::Box2D logoDraw = ML::Box2D((ge->screenWidth - logoSrc.w) / 2, (ge->screenHeight - logoSrc.h) / 4, logoSrc.w, logoSrc.h);
		res->imgTitle->Draw(logoDraw, logoSrc);

		// メニュー
		ML::Color textColor = ML::Color(1.0f, 1.0f, 1.0f, 1.0f);
		ML::Box2D firstMenuDrawBox = ML::Box2D(0, ge->screenHeight * 0.6f, ge->screenWidth, Font::smallDefaultFontSize);
		int menuSpacing = 20;
		string menuStrings[Menu::EnumEnd] = { "スタート", "終了" };
		for (int i = 0; i < Menu::EnumEnd; ++i) {
			ML::Box2D menuDraw = firstMenuDrawBox.OffsetCopy(0, i * (Font::smallDefaultFontSize + menuSpacing));
			Font::smallDefaultFont->Draw(menuDraw, menuStrings[i], textColor, DT_CENTER);

			if (selectingMenu == i) {
				int arrowSize = 16;
				ML::Box2D arrowDraw = ML::Box2D(ge->screenWidth / 3, menuDraw.y + (Font::smallDefaultFontSize - arrowSize) / 2, arrowSize, arrowSize);
				ML::Box2D arrowSrc = ML::Box2D(0, 0, arrowSize, arrowSize);
				res->imgArrow->Draw(arrowDraw, arrowSrc, ML::Color(1.0f, 0.0f, 1.0f, 0.0f));
			}
		}
	}

#pragma endregion
}