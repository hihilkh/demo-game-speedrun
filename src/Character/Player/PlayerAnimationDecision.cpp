#include "GE/GEHeader.h"
#include "PlayerAnimationDecision.h"
#include "PlayerModel.h"

namespace Player
{
	namespace
	{
		const std::string animClipName_Idle = "idle";
		const std::string animClipName_Walk = "walk";
		const std::string animClipName_PrepareToRun = "prepare_to_run";
		const std::string animClipName_Run = "run";
		const std::string animClipName_StopRunning = "stop_running";
		const std::string animClipName_Fallback = "fallback";

		std::string GetAnimClipNameWithDir(const std::string& animClipName, TransformUtils::Direction dir)
		{
			using namespace TransformUtils;
			switch (dir) {
				case Direction::Down:	return animClipName + "_down";
				case Direction::Left:	return animClipName + "_left";
				case Direction::Up:		return animClipName + "_up";
				case Direction::Right:	return animClipName + "_right";
			}

			assert(false && "おかしい方向");

			// 警告を出さないように
			return "";
		}
	}

	PlayerAnimationDecision::PlayerAnimationDecision(PlayerModel& model) :
		GE::Animation::AnimationDecision(),
		model(model)
	{
	}

	std::string PlayerAnimationDecision::DecideCurrentClip()
	{
		PlayerState state = model.GetPlayerState();

		std::string animClipName = animClipName_Idle;
		switch (state) {
			case PlayerState::PrepareToRun:	animClipName = animClipName_PrepareToRun;	break;
			case PlayerState::Run:			animClipName = animClipName_Run;			break;
			case PlayerState::StopRunning:	animClipName = animClipName_StopRunning;	break;
			case PlayerState::Fallback:		animClipName = animClipName_Fallback;		break;
			case PlayerState::Walk:
				if (model.GetMoveDirVector() == Vector2::zero) {
					animClipName = animClipName_Idle;
				} else {
					animClipName = animClipName_Walk;
				}
				break;
		}

		return GetAnimClipNameWithDir(animClipName, model.GetFacingDirection());
	}
}