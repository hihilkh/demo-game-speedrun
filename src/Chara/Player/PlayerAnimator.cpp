#include "PlayerAnimator.h"
#include "Utils/Log.h"
#include "Animation/AnimationClip.h"
#include "PlayerConstant.h"

namespace Player
{
	using namespace Animation;
	using namespace PlayerConstant;

	// TODO : Study why AnimationClip would be copied here
	// TODO : Study how to use move construction for it / reduce constructor call
	unordered_map<PlayerState, AnimationClip> PlayerAnimator::AnimClipMap = {
		{ PlayerState::Idle, AnimationClip({ 
			AnimationKey(0, 0, RenderWidth, RenderHeight, 1), }) 
		},

		{ PlayerState::Walk, AnimationClip({
			AnimationKey(0, 0				, RenderWidth, RenderHeight, 5),
			AnimationKey(0, RenderHeight	, RenderWidth, RenderHeight, 10),
			AnimationKey(0, RenderHeight * 2, RenderWidth, RenderHeight, 15),
			AnimationKey(0, RenderHeight * 3, RenderWidth, RenderHeight, 20), })
		},
	};

	PlayerAnimator::PlayerAnimator(Player::Object::WP player, Player::Resource::WP res) :
		player(player),
		res(res),
		currentPlayerState(PlayerState::Idle),
		currentAnimFrame(0),
		pCurrentAnimClip(nullptr)
	{
		UpDateCurrentAnimClip();
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
			++currentAnimFrame;
			if (currentAnimFrame >= pCurrentAnimClip->GetAnimLength()) {
				currentAnimFrame -= pCurrentAnimClip->GetAnimLength();
			}
		}
	}

	void PlayerAnimator::ChangeState(PlayerState to)
	{
		currentPlayerState = to;
		currentAnimFrame = 0;
		UpDateCurrentAnimClip();
	}

	void PlayerAnimator::UpDateCurrentAnimClip()
	{
		try {
			pCurrentAnimClip = &AnimClipMap.at(currentPlayerState);
		}
		catch (...) {
			PrintWarning("pCurrentAnimClipは探せない");
			pCurrentAnimClip = nullptr;
		}
	}

	void PlayerAnimator::Render(const ML::Box2D& drawBase, const ML::Point& cameraOffset)
	{
		if (!pCurrentAnimClip) {
			return;
		}

		Player::Object::SP playerSP = player.lock();
		if (!playerSP) {
			return;
		}

		Player::Resource::SP resSP = res.lock();
		if (!resSP) {
			return;
		}

		ML::Box2D draw = drawBase.OffsetCopy(cameraOffset);
		ML::Box2D src = pCurrentAnimClip->GetImageSrc(currentAnimFrame);
		UpdateSrcDirection(src, playerSP->GetDirection());

		resSP->img->Draw(draw, src);
	}

	void PlayerAnimator::UpdateSrcDirection(ML::Box2D& outSrc, Direction direction) const
	{
		outSrc.x += static_cast<int>(direction) * RenderWidth;
	}
}