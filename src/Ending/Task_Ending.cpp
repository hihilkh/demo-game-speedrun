//-------------------------------------------------------------------
//エンディング
//-------------------------------------------------------------------
#include "MyPG.h"
#include "Task_Ending.h"
#include "Game/Task_Game.h"
#include "Title/Task_Title.h"
#include "Task/TaskConstant.h"
#include "SceneTransition/Task_SceneTransition.h"
#include "Common/Font.h"
#include "Game/GameStatus.h"

namespace Ending
{
#pragma region Resource

	Resource::Resource()
	{
		imgArrow = DG::Image::Create(GetImagePath(ResourceConstant::ArrowImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	enum Menu
	{
		Retry = 0,
		BackToMainMenu = 1,
		EnumEnd = 2,
	};

	Object::Object() : 
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Ending, TaskConstant::TaskName_Default),
		isInteractable(false)
	{
		render2D_Priority[1] = 0.5f;

		SceneTransition::Fade(false, [this]() { this->isInteractable = true; });
	}

	Object::~Object()
	{
		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
			switch (selectingMenu) {
				case Menu::Retry:	Game::Object::Create(true);	break;
				case Menu::BackToMainMenu:	Title::Object::Create(true);	break;
			}
		}
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		if (!isInteractable) {
			return;
		}

		auto inp = ge->in1->GetState();

		if (inp.LStick.BU.down) {
			selectingMenu = max(selectingMenu - 1, 0);
		}
		else if (inp.LStick.BD.down) {
			selectingMenu = min(selectingMenu + 1, Menu::EnumEnd - 1);
		}

		if (inp.B2.down) {
			SceneTransition::Fade(true, [this]() { this->Kill(); });
			isInteractable = false;
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Color textColor = ML::Color(1.0f, 1.0f, 1.0f, 1.0f);
		ML::Color timeTextColor = ML::Color(1.0f, 1.0f, 0.8f, 0.2f);

		// 成績
		ML::Box2D congratsDraw = ML::Box2D(0, ge->screenHeight / 5, ge->screenWidth, Font::largeDefaultFontSize);
		Font::largeDefaultFont->Draw(congratsDraw, "おめでとうございます！", textColor, DT_CENTER);

		float timeTextSpacing = 10;
		ML::Box2D timeTextDraw = congratsDraw.OffsetCopy(0.0f, Font::largeDefaultFontSize + timeTextSpacing);
		string timeText = format("クリア時間：{0:.3f}s", Game::GameStatus::ClearGameTimeMillisecond / 1000.0f);
		Font::largeDefaultFont->Draw(timeTextDraw, timeText, timeTextColor, DT_CENTER);

		// メニュー
		int menuWidth = ge->screenWidth / 3;
		ML::Box2D firstMenuDrawBox = ML::Box2D((ge->screenWidth - menuWidth) / 2, ge->screenHeight * 0.6f, menuWidth, Font::smallDefaultFontSize);
		int menuSpacing = 20;
		string menuStrings[Menu::EnumEnd] = { "リトライ", "タイトル" };
		for (int i = 0; i < Menu::EnumEnd; ++i) {
			ML::Box2D menuDraw = firstMenuDrawBox.OffsetCopy(0, i * (Font::smallDefaultFontSize + menuSpacing));
			Font::smallDefaultFont->Draw(menuDraw, menuStrings[i], textColor, DT_CENTER);

			if (selectingMenu == i) {
				int arrowSize = 16;
				ML::Box2D arrowDraw = ML::Box2D(menuDraw.x - arrowSize, menuDraw.y + (Font::smallDefaultFontSize - arrowSize) / 2, arrowSize, arrowSize);
				ML::Box2D arrowSrc = ML::Box2D(0, 0, arrowSize, arrowSize);
				res->imgArrow->Draw(arrowDraw, arrowSrc, ML::Color(1.0f, 0.0f, 1.0f, 0.0f));
			}
		}
	}

#pragma endregion
}