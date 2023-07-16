#include "GE/GEHeader.h"
#include "TempPlayerAnimator.h"
#include "PlayerModel.h"
#include "GE/Render/Image.h"
#include "Character/Player/PlayerRenderInfo.h"

namespace Player
{
	TempPlayerAnimator::TempPlayerAnimator(GameObject& gameObject, PlayerModel& model, Image& image) :
		Component(gameObject),
		model(model),
		image(image)
	{
	}

	void TempPlayerAnimator::LateUpdate()
	{
		TransformUtils::Direction dir = model.GetFacingDirection();
		int dirInt = static_cast<int>(dir);
		RectPixel srcRect(dirInt * playerWidth, 0, playerWidth, playerHeight);
		image.SetSrcRect(srcRect);
	}
}