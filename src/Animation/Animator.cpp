#include "Animator.h"
#include "Animation/AnimationClip.h"
#include <DG2014/DG2014_Image.h>
#include "Debug/Log.h"

namespace Animation
{
	// TODO : Move semanticsを適用できるか
	// TODO : AnimatorのUpDateモジュールを作る
	Animator::Animator(DG::Image::SP img, const initializer_list<AnimationClip>& animClips) :
		img(img),
		animClips(animClips),
		pCurrentAnimClip(nullptr),
		currentAnimFrame(0),
		isPlaying(true)
	{
		SetAnimClip(0);
	}

	Animator::~Animator()
	{
	}

	void Animator::UpDate()
	{
		if (!isPlaying) {
			return;
		}

		if (!pCurrentAnimClip) {
			return;
		}

		++currentAnimFrame;
		if (currentAnimFrame >= pCurrentAnimClip->GetAnimLength()) {
			if (pCurrentAnimClip->GetIsLoop()) {
				currentAnimFrame -= pCurrentAnimClip->GetAnimLength();
			}
			else {
				currentAnimFrame = pCurrentAnimClip->GetAnimLength();
				isPlaying = false;
			}
		}
	}

	void Animator::SetAnimClip(int index)
	{
		if (index >= animClips.size()) {
			DEBUG_LOG_WARNING("index は animClips.size() に超える");
			return;
		}

		if (pCurrentAnimClip == &animClips[index]) {
			DEBUG_LOG("すでにターゲットAnimClipです");
			return;

		}

		pCurrentAnimClip = &animClips[index];
		currentAnimFrame = 0;
		isPlaying = true;
	}

	void Animator::Render(const ML::Box2D& draw)
	{
		if (!pCurrentAnimClip) {
			return;
		}

		ML::Box2D src = pCurrentAnimClip->GetImageSrc(currentAnimFrame);
		img->Draw(draw, src);
	}
}