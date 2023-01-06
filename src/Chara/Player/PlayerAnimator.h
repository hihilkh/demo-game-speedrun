#pragma once

#include "Task_Player.h"

#pragma region 前方宣言

namespace Animation { class AnimationClip; }

#pragma endregion

namespace Player
{
	class PlayerAnimator
	{
	private:
		PlayerAnimator(const PlayerAnimator&) = delete;

	public:
		PlayerAnimator(Player::Object::WP player, Player::Resource::WP res);
		~PlayerAnimator();

	private:
		Player::Object::WP player;
		Player::Resource::WP res;

		PlayerState currentPlayerState;
		int currentAnimFrame;
		Animation::AnimationClip* pCurrentAnimClip;

		static unordered_map<PlayerState, Animation::AnimationClip> AnimClipMap;

	private:
		void ChangeState(PlayerState to);
		void UpdateCurrentAnimClip();
		void UpdateSrcDirection(ML::Box2D& outSrc, Direction direction) const;


	public:
		void UpDate();
		void Render(const ML::Box2D& drawBase, const ML::Point& cameraOffset);
	};
}