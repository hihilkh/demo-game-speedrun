#include "GE/GEHeader.h"
#include "GameProgress.h"

namespace GameScene
{
	GameProgress GameProgress::currerntGameProgress;

	GameProgress::GameProgress() :
		gameClearTime(-1.0f)
	{
	}

	GameProgress& GameProgress::CreateNewGameProgress()
	{
		GameProgress::currerntGameProgress = GameProgress();
		return GameProgress::currerntGameProgress;
	}

	GameProgress& GameProgress::GetCurrentGameProgress()
	{
		return GameProgress::currerntGameProgress;
	}


}