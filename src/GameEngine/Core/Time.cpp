#include "Time.h"

#include <chrono>

namespace GE
{
	namespace
	{
		std::chrono::time_point<std::chrono::steady_clock> clockTime;
	}

	float Time::currentTime = - 1.0f;
	float Time::deltaTime = 1.0f;
	float Time::timeScale = -1.0f;

	void Time::Init(int targetFps)
	{
		currentTime = 0.0f;
		timeScale = 1.0f;

		// deltaTimeを0にならないように、1フレームを過ごしたとみなし
		clockTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(1000 / targetFps);
		Update();
	}

	void Time::Update()
	{
		auto now = std::chrono::steady_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - clockTime);
		deltaTime = microseconds.count() / 1000000.0f;

		deltaTime *= timeScale;

		currentTime += deltaTime;
		clockTime = now;
	}
}