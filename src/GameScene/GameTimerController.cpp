#include "GE/GEHeader.h"
#include "GameTimerController.h"
#include "TimeUtils/Timer.h"
#include "GE/UI/Text.h"
#include <format>

namespace GameScene
{
	GameTimerController::GameTimerController(GameObject& gameObject, TimeUtils::Timer& timer, GE::UI::Text& text) :
		Component(gameObject),
		timer(timer),
		text(text)
	{
	}

	void GameTimerController::Update()
	{
		text.SetText(std::format("{0:.3f}s", timer.GetCountedTime()));
	}

	void GameTimerController::StartTimer()
	{
		timer.StartTimer();
	}

	void GameTimerController::PauseTimer()
	{
		timer.PauseTimer();
	}

	float GameTimerController::GetCountedTime() const
	{
		return timer.GetCountedTime();
	}
}