#include "GE/GEHeader.h"
#include "Timer.h"

namespace TimeUtils
{
	Timer::Timer(GameObject& gameObject) :
		Component(gameObject)
	{
		ResetTimer();
	}

	bool Timer::StartTimer()
	{
		if (state == State::Stopped) {
			countedTime = 0.0f;
			state = State::Started;
			return true;
		} else {
			DEBUG_LOG_WARNING("Timerはすでにスタートした。再びスタートできない。");
			return false;
		}
	}

	bool Timer::PauseTimer()
	{
		if (state == State::Stopped) {
			DEBUG_LOG_WARNING("Timerはまだスタートしていない。ポーズできない。");
			return false;
		} else {
			state = State::Paused;
			return true;
		}
	}

	bool Timer::UnpauseTimer()
	{
		if (state == State::Stopped) {
			DEBUG_LOG_WARNING("Timerはまだスタートしていない。ポーズの解除することができない。");
			return false;
		} else {
			state = State::Started;
			return true;
		}
	}

	void Timer::ResetTimer()
	{
		countedTime = 0.0f;
		state = State::Stopped;
	}

	void Timer::Update()
	{
		switch (state) {
			case State::Stopped:
			case State::Paused:
				return;
		}

		countedTime += Time::GetDeltaTime();
	}
}