#pragma once

#include <string>

namespace TaskConstant {

#pragma region TaskGroupName

	const std::string TaskGroupName_Title = "タイトル";
	const std::string TaskGroupName_Ending = "エンディング";

	const std::string TaskGroupName_Game = "本編";
	const std::string TaskGroupName_Map = "マップ";
	const std::string TaskGroupName_MapObject = "マップオブジェクト";
	const std::string TaskGroupName_Chara = "キャラクター";

	const std::string TaskGroupName_ParticleSystem = "パーティクルシステム";
	const std::string TaskGroupName_SceneTransition = "シーントランジション";

	const std::string TaskGroupName_Debug = "デバッグ";

#pragma endregion

#pragma region TaskName

	const std::string TaskName_Default = "NoName";

	const std::string TaskName_Game = "統括";
	const std::string TaskName_GameCamera = "カメラ";
	const std::string TaskName_Map = "統括";
	const std::string TaskName_Goal = "終点";
	const std::string TaskName_Player = "プレイヤー";

	const std::string TaskName_Profiler = "プロファイラ";
#pragma endregion
}