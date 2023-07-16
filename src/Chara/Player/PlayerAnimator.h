#pragma once

/* TODO

#include <myLib.h>
#include "Event/Event.tpp"
#include "Common/Direction.h"
#include "PlayerState.h"

#pragma region 前方宣言

namespace Animation { class AnimationClip; }
namespace Player {
	class Object;
	class Resource;
}

#pragma endregion

namespace Player
{
	class PlayerAnimator
	{
	private:
		PlayerAnimator(const PlayerAnimator&) = delete;

	public:
		PlayerAnimator(weak_ptr<Player::Object> player, shared_ptr<Player::Resource> res);
		~PlayerAnimator();

	private:
		weak_ptr<Player::Object> player;
		shared_ptr<Player::Resource> res;

		PlayerState currentPlayerState;
		int currentAnimFrame;
		const Animation::AnimationClip* pCurrentAnimClip;

		static const unordered_map<PlayerState, Animation::AnimationClip> AnimClipMap;

		bool isPlaying;

	public:
		Event<PlayerState> animFinished;

	private:
		void ChangeState(PlayerState to);
		void UpdateCurrentAnimClip();
		void UpdateSrcDirection(ML::Box2D& outSrc, Direction direction) const;


	public:
		void UpDate();
		void Render(const ML::Box2D& drawBase, const ML::Point& cameraOffset, int height);
	};
}

*/