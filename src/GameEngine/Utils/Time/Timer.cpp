#include "Timer.h"

namespace Time
{
	Timer::Timer() :
		isStarted(false),
		isRunning(false),
		startTime(),
		durationForPause()
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::Start()
	{
		startTime = std::chrono::steady_clock::now();
		isStarted = true;
		isRunning = true;
	}

	void Timer::Pause()
	{
		if (isRunning) {
			durationForPause = GetCurrentDuration();
			isRunning = false;
		}
	}

	void Timer::Unpause()
	{
		if (!isRunning) {
			startTime = std::chrono::steady_clock::now() - durationForPause;
			isRunning = true;
		}
	}

	void Timer::Reset()
	{
		isStarted = false;
		isRunning = false;
	}

	std::chrono::milliseconds Timer::GetCurrentDuration() const
	{
		auto now = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
	}

	int Timer::GetCurrentCountMillisecond() const
	{
		if (!isStarted) {
			return 0;
		}

		if (!isRunning) {
			return (int)durationForPause.count();
		}

		return (int)GetCurrentDuration().count();
	}
}