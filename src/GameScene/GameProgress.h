#pragma once

namespace GameScene
{
	class GameProgress
	{
	public:
		static GameProgress& CreateNewGameProgress();
		static GameProgress& GetCurrentGameProgress();

		float GetGameClearTime() const { return gameClearTime; }
		void SetGameClearTime(float time) { gameClearTime = time; }

	private:
		static GameProgress currerntGameProgress;
		float gameClearTime;

	private:
		GameProgress();
	};
}