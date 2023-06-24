#pragma once

namespace GE
{
	/// <summary>
	/// タイムの単位：秒
	/// </summary>
	class Time
	{
		friend class GameEngine;

	public:
		static float GetTime() { return currentTime; }
		static float GetDeltaTime() { return deltaTime; }
		static float GetTimeScale() { return timeScale; }
		static void SetTimeScale(float scale) { timeScale = scale; }

	private:
		static float currentTime;
		static float deltaTime;
		static float timeScale;

	private:
		Time() = delete;
		static void Init(int targetFps);
		static void OnUpdate();
	};
}