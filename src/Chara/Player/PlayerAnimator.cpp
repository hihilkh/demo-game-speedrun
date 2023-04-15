#include "PlayerAnimator.h"
#include "Debug/Log.h"
#include "Animation/AnimationClip.h"
#include "Task_Player.h"
#include "Task/ResourceConstant.h"

namespace Player
{
	using namespace Animation;
	using namespace ResourceConstant;

	// TODO : Animatorに合わせる
	// TODO : 何故ここはAnimationClipをコーヒーするか？
	// TODO : コンストラクタの呼び出しを減少
	// TODO : static又はインスタンス？
	const unordered_map<PlayerState, AnimationClip> PlayerAnimator::AnimClipMap = {
		{ PlayerState::Idle, AnimationClip(true, {
			AnimationKey(0, 0, PlayerImageWidth, PlayerImageHeight, 1), })
		},

		{ PlayerState::Walk, AnimationClip(true, {
			AnimationKey(0, 0					 , PlayerImageWidth, PlayerImageHeight, 6),
			AnimationKey(0, PlayerImageHeight	 , PlayerImageWidth, PlayerImageHeight, 12),
			AnimationKey(0, PlayerImageHeight * 2, PlayerImageWidth, PlayerImageHeight, 18),
			AnimationKey(0, PlayerImageHeight * 3, PlayerImageWidth, PlayerImageHeight, 24), })
		},

		// 一時的なコード
		{ PlayerState::Attack, AnimationClip(false, {
			AnimationKey(0, 0					 , PlayerImageWidth, PlayerImageHeight, 5),
			AnimationKey(0, PlayerImageHeight	 , PlayerImageWidth, PlayerImageHeight, 10),
			AnimationKey(0, PlayerImageHeight * 2, PlayerImageWidth, PlayerImageHeight, 15),
			AnimationKey(0, PlayerImageHeight * 3, PlayerImageWidth, PlayerImageHeight, 20), })
		},

		// 一時的なコード
		{ PlayerState::PrepareToRun, AnimationClip(true, {
			AnimationKey(0, 0					 , PlayerImageWidth, PlayerImageHeight, 3),
			AnimationKey(0, PlayerImageHeight	 , PlayerImageWidth, PlayerImageHeight, 6),
			AnimationKey(0, PlayerImageHeight * 2, PlayerImageWidth, PlayerImageHeight, 9),
			AnimationKey(0, PlayerImageHeight * 3, PlayerImageWidth, PlayerImageHeight, 12), })
		},

		// 一時的なコード
		{ PlayerState::Running, AnimationClip(true, {
			AnimationKey(0, 0					 , PlayerImageWidth, PlayerImageHeight, 3),
			AnimationKey(0, PlayerImageHeight	 , PlayerImageWidth, PlayerImageHeight, 6),
			AnimationKey(0, PlayerImageHeight * 2, PlayerImageWidth, PlayerImageHeight, 9),
			AnimationKey(0, PlayerImageHeight * 3, PlayerImageWidth, PlayerImageHeight, 12), })
		},

		// 一時的なコード
		{ PlayerState::Stopping, AnimationClip(true, {
			AnimationKey(0, 0, PlayerImageWidth, PlayerImageHeight, 1), })
		},

		// 一時的なコード
		{ PlayerState::Fallback, AnimationClip(true, {
			AnimationKey(0, 0, PlayerImageWidth, PlayerImageHeight, 1), })
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
		auto playerSP = player.lock();
		if (!playerSP) {
			DEBUG_LOG_WARNING("プレイヤーの参照が取れない");
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
			DEBUG_LOG_WARNING("pCurrentAnimClipは探せない");
			pCurrentAnimClip = nullptr;
		}
	}

	void PlayerAnimator::Render(const ML::Box2D& drawBase, const ML::Point& cameraOffset, int height)
	{
		if (!pCurrentAnimClip) {
			return;
		}

		auto playerSP = player.lock();
		if (!playerSP) {
			return;
		}

		// 影 = コライダーの位置
		ML::Box2D shadowDraw = playerSP->GetCurrentHitBox().OffsetCopy(cameraOffset);
		res->shadowImg->Draw(shadowDraw, PlayerShadowSrc);

		// プレイヤー
		ML::Box2D playerDraw = drawBase.OffsetCopy(cameraOffset);
		playerDraw.y -= height;
		ML::Box2D playerSrc = pCurrentAnimClip->GetImageSrc(currentAnimFrame);
		UpdateSrcDirection(playerSrc, playerSP->transform->direction);
		res->playerImg->Draw(playerDraw, playerSrc);
	}

	void PlayerAnimator::UpdateSrcDirection(ML::Box2D& outSrc, Direction direction) const
	{
		outSrc.x += static_cast<int>(direction) * PlayerImageWidth;
	}
}