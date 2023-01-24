#pragma once

#include <memory>
#include <vector>
#include <initializer_list>
#include "AnimationClip.h"

#pragma region 前方宣言

namespace DG { class Image; }
namespace ML { class Box2D; }

#pragma endregion

namespace Animation
{


	class Animator
	{
	private:
		Animator(const Animator&) = delete;

	public:
		Animator(std::shared_ptr<DG::Image> img, const std::initializer_list<AnimationClip>& animClips);
		~Animator();

	private:
		std::shared_ptr<DG::Image> img;
		std::vector<AnimationClip> animClips;

		AnimationClip* pCurrentAnimClip;
		int currentAnimFrame;

		bool isPlaying;

	public:
		void SetAnimClip(int index);
		void UpDate();
		void Render(const ML::Box2D& draw);
	};
}