#include "GE/GEHeader.h"
#include "PlayerFallbackStateHandler.h"
#include "Character/Player/PlayerConfig.h"
#include "Character/Player/PlayerRenderInfo.h"
#include "Character/Player/PlayerModel.h"
#include <numbers>

namespace Player
{
	PlayerFallbackStateHandler::PlayerFallbackStateHandler(PlayerModel& model) :
		PlayerStateHandler(model, PlayerState::Fallback),
		normalizedFallbackTime(0.0f),
		playerImageTransform(nullptr),
		fallbackVelocity()
	{
	}

	void PlayerFallbackStateHandler::OnEnter()
	{
		normalizedFallbackTime = 0.0f;

		auto playerImageObject = GE::FindGameObject(playerImageObjectName);
		if (playerImageObject) {
			playerImageTransform = &playerImageObject->GetTransform();
		}

		TransformUtils::Direction facingDir = model.GetFacingDirection();
		fallbackVelocity = GetDirectionalVector(facingDir);
		fallbackVelocity *= -fallbackSpeed;
	}

	void PlayerFallbackStateHandler::OnUpdate()
	{
		float deltaNormalizedFallbackTime = Time::GetDeltaTime() / fallbackPeriod;

		// normalizedFallbackTimeを1に超えないように
		deltaNormalizedFallbackTime = std::min(deltaNormalizedFallbackTime, 1 - normalizedFallbackTime);
		normalizedFallbackTime += deltaNormalizedFallbackTime;

		// playerImageの高さ
		// TODO : Animatorで制御するようになる
		if (playerImageTransform == nullptr) {
			DEBUG_LOG_WARNING("playerImageTransform == nullptr。FallbackのUpdateがうまくいかない。");
		} else {
			float playerImageHeight = fallbackMaxHeight * std::sin(normalizedFallbackTime * (float)std::numbers::pi);
			playerImageTransform->SetPosY(playerImageHeight);
		}

		// playerの位置
		Vector2 newPos = model.GetTransform().GetPos() + fallbackVelocity * deltaNormalizedFallbackTime * fallbackPeriod;
		model.GetTransform().SetPos(newPos);
	}

	bool PlayerFallbackStateHandler::CheckHasDoneState()
	{
		return normalizedFallbackTime >= 1;
	}
}

