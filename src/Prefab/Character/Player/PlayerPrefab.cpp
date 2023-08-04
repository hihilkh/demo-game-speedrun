#include "GE/GEHeader.h"
#include "PlayerPrefab.h"

#include "Prefab/Camera/MainCameraPrefab.h"

#include "GE/Render/Image.h"
#include "Rendering/RenderPriority.h"

#include "Character/Player/PlayerModel.h"
#include "Character/Player/PlayerController.h"
#include "Character/Player/PlayerRenderInfo.h"
#include "Character/Player/PlayerCameraController.h"
#include "Character/Player/PlayerCollisionHandler.h"
#include "Character/Player/PlayerAnimationDecision.h"

#include "GE/Collision/RectCollider.h"
#include "Collision/CollisionInfo.h"

#include "GE/Animation/Animator.h"

namespace Prefab::Player
{
	::Player::PlayerModel& PlayerPrefab::operator()(GameObject& baseGameObject) const
	{
		baseGameObject.SetName("Player");

		// ゲームカメラ
		auto& camera = GE::Instantiate(Prefab::Camera::MainCameraPrefab(), &baseGameObject);
		camera.gameObject.AddComponent<::Player::PlayerCameraController>(camera);

		GameObject& imageBase = baseGameObject.AddChild("ImageBase");
		imageBase.GetTransform().SetPosY(::Player::playerHeight / 2);

		// playerImage
		GameObject& playerImageObject = imageBase.AddChild(::Player::playerImageObjectName);
		RectPixel playerImgSrcRect(0, 0, ::Player::playerWidth, ::Player::playerHeight);
		auto& playerImage = playerImageObject.AddComponent<Image>("./data/Image/Chara.png", playerImgSrcRect);
		playerImage.SetRenderPriority(RenderPriority::player);

		// shadowImage
		GameObject& shadowImageObject = imageBase.AddChild("ShadowImage");
		shadowImageObject.GetTransform().SetPosY(-::Player::playerHeight / 2);
		RectPixel playerShadowSrcRect(0, 0, ::Player::shadowWidth, ::Player::shadowHeight);
		auto& shadowImage = shadowImageObject.AddComponent<Image>("./data/Image/Shadow.png", playerShadowSrcRect);
		shadowImage.SetRenderPriority(RenderPriority::player - 1);

		// Collider
		auto& collider = baseGameObject.AddComponent<RectCollider>(
			false,
			true,
			Rect::FromCenter((float)::Player::shadowWidth, (float)::Player::shadowHeight));
		collider.SetCollisionLayer(CollisionInfo::playerLayer);

		auto& model = baseGameObject.AddComponent<::Player::PlayerModel>();
		auto& controller = baseGameObject.AddComponent<::Player::PlayerController>(model);
		auto& collisionHandler = baseGameObject.AddComponent<::Player::PlayerCollisionHandler>(model, collider);
		auto& animator = baseGameObject.AddComponent<Animator>(
			"./data/Animation/Player.json", 
			std::make_unique<::Player::PlayerAnimationDecision>(model));
		animator.SetImage(&playerImage);

		return model;
	}
}
