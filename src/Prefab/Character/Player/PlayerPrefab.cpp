#include "GE/GEHeader.h"
#include "PlayerPrefab.h"

#include "Prefab/Camera/MainCameraPrefab.h"

#include "GE/Render/Image.h"
#include "Common/RenderPriority.h"

#include "Character/Player/PlayerModel.h"
#include "Character/Player/PlayerController.h"
#include "Character/Player/PlayerRenderInfo.h"

#include "GE/Collision/RectCollider.h"
#include "Common/CollisionInfo.h"

namespace Prefab::Player
{
	::Player::PlayerModel& PlayerPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName("Player");

		// ゲームカメラ
		GE::Instantiate(Prefab::Camera::MainCameraPrefab(), &baseGameObject);

		GameObject& imageBase = baseGameObject.AddChild("ImageBase");
		imageBase.GetTransform().pos.y = ::Player::playerHeight / 2;

		// playerImage
		GameObject& playerImageObject = imageBase.AddChild("PlayerImage");
		RectPixel playerImgSrcRect(0, 0, ::Player::playerWidth, ::Player::playerHeight);
		auto& playerImage = playerImageObject.AddComponent<GE::Render::Image>("./data/Image/Chara.png", playerImgSrcRect);
		playerImage.SetRenderPriority(RenderPriority::player);

		// shadowImage
		GameObject& shadowImageObject = imageBase.AddChild("ShadowImage");
		shadowImageObject.GetTransform().pos.y = -::Player::playerHeight / 2;
		RectPixel playerShadowSrcRect(0, 0, ::Player::shadowWidth, ::Player::shadowHeight);
		auto& shadowImage = shadowImageObject.AddComponent<GE::Render::Image>("./data/Image/Shadow.png", playerShadowSrcRect);
		shadowImage.SetRenderPriority(RenderPriority::player - 1);

		// Collider
		auto& collider = baseGameObject.AddComponent<GE::Collision::RectCollider>(
			false,
			Rect::FromCenter((float)::Player::shadowWidth, (float)::Player::shadowHeight));
		collider.SetCollisionLayer(CollisionInfo::playerLayer);

		auto& model = baseGameObject.AddComponent<::Player::PlayerModel>();
		auto& controller = baseGameObject.AddComponent<::Player::PlayerController>();

		return model;
	}
}
