#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <string>


namespace GE
{
	namespace UI
	{
		class Text;
	}
}

namespace UI
{
	class CountDownUI : public Component
	{
	public:
		CountDownUI(GameObject& gameObject, GE::UI::Text& text);
		void StartCountDown(int second, std::string finishCountDownText, std::function<void()> onFinished = nullptr);

	protected:
		void Start() override;
		void Update() override;

	private:
		GE::UI::Text& text;

		float startTime;
		int startCountDownSecond;
		std::string finishCountDownText;

		std::function<void()> onFinished;

	private:
		void SetCountDownText(const std::string& countDownText);
		void FinishCountDown();
	};
}