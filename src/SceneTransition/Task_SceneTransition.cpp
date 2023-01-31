#include "Task_SceneTransition.h"
#include "Task/TaskConstant.h"

namespace SceneTransition
{
#pragma region Resource

	Resource::Resource()
	{
		img = DG::Image::Create(GetImagePath(ResourceConstant::WhiteImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_SceneTransition, TaskConstant::TaskName_Default, true),
		currentState(State::FadedOut),
		totalFadeTime(0),
		currentFadeTime(0),
		onFinishedFading(nullptr)
	{
		render2D_Priority[1] = 0.0f;
	}

	Object::~Object()
	{
	}

	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void Object::UpDate()
	{
		switch (currentState)
		{
			case State::FadedOut:
			case State::FadedIn:
				break;
			case State::FadingIn:
			case State::FadingOut:
				++currentFadeTime;
				if (currentFadeTime >= totalFadeTime) {
					currentState = currentState == State::FadingIn ? State::FadedIn : State::FadedOut;
					if (onFinishedFading) {
						onFinishedFading();
						onFinishedFading = nullptr;
					}
				}
				break;
		}
	}

	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void Object::Render2D_AF()
	{
		ML::Box2D draw = ML::Box2D(0, 0, ge->screenWidth, ge->screenHeight);
		ML::Box2D src = ML::Box2D(0, 0, 32, 32);
		ML::Color color = ML::Color(CalculateCurrentAlpha(), 0.0f, 0.0f, 0.0f);

		res->img->Draw(draw, src, color);
	}

	float Object::CalculateCurrentAlpha() const
	{
		float from = 0.0f;
		float to = 1.0f;

		switch (currentState)
		{
			case State::FadedOut:	return 0.0f;
			case State::FadedIn:	return 1.0f;
			case State::FadingIn:	from = 0.0f;	to = 1.0f;	break;
			case State::FadingOut:	from = 1.0f;	to = 0.0f;	break;
		}

		if (totalFadeTime == 0) {
			return to;
		}

		return std::lerp(from, to, (float)currentFadeTime / totalFadeTime);
	}

	void Object::Fade(bool isFadeIn, int fadeTime, std::function<void()> onFinished)
	{
		onFinishedFading = onFinished;
		totalFadeTime = fadeTime;
		currentFadeTime = 0;
		currentState = isFadeIn ? State::FadingIn : State::FadingOut;
	}

#pragma endregion

	namespace
	{
		static const int DefaultFadeTime = 30;
	}

	void Fade(bool isFadeIn, std::function<void()> onFinished)
	{
		Fade(isFadeIn, DefaultFadeTime, onFinished);
	}

	void Fade(bool isFadeIn, int fadeTime, std::function<void()> onFinished)
	{
		Object::SP sceneTransition = ge->GetTask<Object>(TaskConstant::TaskGroupName_SceneTransition);
		if (!sceneTransition) {
			sceneTransition = Object::Create(true);
		}

		sceneTransition->Fade(isFadeIn, fadeTime, onFinished);
	}
}