#include "PlayerAnimator.h"
#include "Utils/Log.h"
#include "Animation/AnimationClip.h"
#include "PlayerConstant.h"
#include "Task_Player.h"

namespace Player
{
	using namespace Animation;
	using namespace Player::Constant;

	// TODO : Study why AnimationClip would be copied here
	// TODO : Study how to use move construction for it / reduce constructor call
	// TODO : Do it need to make AnimClip instance instead of static?
	unordered_map<PlayerState, AnimationClip> PlayerAnimator::AnimClipMap = {
		{ PlayerState::Idle, AnimationClip(true, {
			AnimationKey(0, 0, RenderWidth, RenderHeight, 1), }) 
		},

		{ PlayerState::Walk, AnimationClip(true, {
			AnimationKey(0, 0				, RenderWidth, RenderHeight, 6),
			AnimationKey(0, RenderHeight	, RenderWidth, RenderHeight, 12),
			AnimationKey(0, RenderHeight * 2, RenderWidth, RenderHeight, 18),
			AnimationKey(0, RenderHeight * 3, RenderWidth, RenderHeight, 24), })
		},

		// 一時的なコード
		{ PlayerState::Attack, AnimationClip(false, {
			AnimationKey(0, 0				, RenderWidth, RenderHeight, 5),
			AnimationKey(0, RenderHeight	, RenderWidth, RenderHeight, 10),
			AnimationKey(0, RenderHeight * 2, RenderWidth, RenderHeight, 15),
			AnimationKey(0, RenderHeight * 3, RenderWidth, RenderHeight, 20), })
		},

		// 一時的なコード
		{ PlayerState::Running, AnimationClip(true, {
			AnimationKey(0, 0				, RenderWidth, RenderHeight, 3),
			AnimationKey(0, RenderHeight	, RenderWidth, RenderHeight, 6),
			AnimationKey(0, RenderHeight * 2, RenderWidth, RenderHeight, 9),
			AnimationKey(0, RenderHeight * 3, RenderWidth, RenderHeight, 12), })
		},

		// 一時的なコード
		{ PlayerState::Stopping, AnimationClip(true, {
			AnimationKey(0, 0, RenderWidth, RenderHeight, 1), })
		},

		// 一時的なコード
		{ PlayerState::Fallback, AnimationClip(true, {
			AnimationKey(0, 0, RenderWidth, RenderHeight, 1), })
		},
	};

	PlayerAnimator::PlayerAnimator(Player::Object::WP player, Player::Resource::SP res) :
		player(player),
		res(res),
		currentPlayerState(PlayerState::Idle),
		currentAnimFrame(0),
		pCurrentAnimClip(nullptr),
		isPlaying(true)
	{
		UpdateCurrentAnimClip();
	}

	PlayerAnimator::~PlayerAnimator()
	{
	}

	void PlayerAnimator::UpDate()
	{
		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			PrintWarning("プレイヤーの参照が取れない");
			return;
		}

		PlayerState newPlayerState = playerSP->GetState();
		if (newPlayerState != currentPlayerState) {
			ChangeState(newPlayerState);
		}
		else {
			if (!isPlaying) {
				return;
			}

			++currentAnimFrame;
			if (currentAnimFrame >= pCurrentAnimClip->GetAnimLength()) {
				if (pCurrentAnimClip->GetIsLoop()) {
					currentAnimFrame -= pCurrentAnimClip->GetAnimLength();
				}
				else {
					currentAnimFrame = pCurrentAnimClip->GetAnimLength();
					animFinished.Invoke(newPlayerState);
					isPlaying = false;
				}
			}
		}
	}

	void PlayerAnimator::ChangeState(PlayerState to)
	{
		currentPlayerState = to;
		currentAnimFrame = 0;
		isPlaying = true;
		UpdateCurrentAnimClip();
	}

	void PlayerAnimator::UpdateCurrentAnimClip()
	{
		try {
			pCurrentAnimClip = &AnimClipMap.at(currentPlayerState);
		}
		catch (...) {
			PrintWarning("pCurrentAnimClipは探せない");
			pCurrentAnimClip = nullptr;
		}
	}

	void PlayerAnimator::Render(const ML::Box2D& drawBase, const ML::Point& cameraOffset, int height)
	{
		if (!pCurrentAnimClip) {
			return;
		}

		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			return;
		}

		// TODO : 影
		ML::Box2D draw = drawBase.OffsetCopy(cameraOffset);
		draw.y -= height;
		ML::Box2D src = pCurrentAnimClip->GetImageSrc(currentAnimFrame);
		UpdateSrcDirection(src, playerSP->GetDirection());

		res->img->Draw(draw, src);
	}

	void PlayerAnimator::UpdateSrcDirection(ML::Box2D& outSrc, Direction direction) const
	{
		outSrc.x += static_cast<int>(direction) * RenderWidth;
	}
}