#include "AnimationSystem.h"
#include "Animator.h"

namespace GE::Animation
{
	std::vector<Animator*> AnimationSystem::animators;

	void AnimationSystem::AddAnimator(Animator& animator)
	{
		animators.push_back(&animator);
	}

	void AnimationSystem::RemoveAnimator(Animator& animator)
	{
		animators.erase(
			std::remove(animators.begin(), animators.end(), &animator), 
			animators.end());
	}

	void AnimationSystem::OnAnimationUpdate()
	{
		for (auto animator : animators) {
			animator->OnAnimationUpdate();
		}
	}
}