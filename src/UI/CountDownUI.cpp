#include "GE/GEHeader.h"
#include "CountDownUI.h"
#include "GE/UI/Text.h"

namespace UI
{
	CountDownUI::CountDownUI(GameObject& gameObject, GE::UI::Text& text) :
		Component(gameObject),
		text(text),
		startTime(-1.0f),
		startCountDownSecond(-1),
		finishCountDownText(""),
		onFinished(nullptr)
	{
	}

	void CountDownUI::Start()
	{
		SetCountDownText("");
	}

	void CountDownUI::StartCountDown(int second, std::string finishCountDownText, std::function<void()> onFinished)
	{
		this->startCountDownSecond = second;
		this->finishCountDownText = finishCountDownText;
		this->onFinished = onFinished;
		this->startTime = Time::GetTime();
	}

	void CountDownUI::Update()
	{
		if (startTime < 0) {
			return;
		}

		float countedTime = Time::GetTime() - startTime;
		int currentCountDownSecond = startCountDownSecond - (int)countedTime;
		if (currentCountDownSecond > 0) {
			SetCountDownText(std::to_string(currentCountDownSecond));
		} else if (currentCountDownSecond == 0) {
			SetCountDownText(finishCountDownText);
		} else {
			FinishCountDown();
		}
	}

	void CountDownUI::SetCountDownText(const std::string& countDownText)
	{
		// TODO : textに影をつける
		text.SetText(countDownText);
	}

	void CountDownUI::FinishCountDown()
	{
		if (onFinished) {
			onFinished();
		}

		GE::Destroy(gameObject);
	}
}
