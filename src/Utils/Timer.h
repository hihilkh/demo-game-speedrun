#pragma once

#include <chrono>

// TODO : GE::Componentに変える
namespace Utils
{
	class Timer
	{
	public:
		Timer();
		~Timer();

	private:
		bool isStarted;
		bool isRunning;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::milliseconds durationForPause;

	private:
		std::chrono::milliseconds GetCurrentDuration() const;

	public:
		void Start();
		void Pause();
		void Unpause();
		void Reset();
		int GetCurrentCountMillisecond() const;
	};
}