#pragma once

#include <vector>

namespace GE
{
	class GameEngine;
}

namespace GE::Animation
{
	class Animator;

	class AnimationSystem
	{
		friend GameEngine;

	public:
		static void AddAnimator(Animator& animator);
		static void RemoveAnimator(Animator& animator);

	private:
		static std::vector<Animator*> animators;

	private:
		static void OnAnimationUpdate();
	};
}