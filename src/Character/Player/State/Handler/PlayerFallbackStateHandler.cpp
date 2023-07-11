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
		startTime(0.0f),
		playerImageTransform(nullptr),
		startPos(),
		finalPos()
	{
	}

	void PlayerFallbackStateHandler::OnEnter()
	{
		startTime = Time::GetTime();

		auto playerImageObject = GE::FindGameObject(playerImageObjectName);
		if (playerImageObject) {
			playerImageTransform = &playerImageObject->GetTransform();
		}

		using namespace TransformUtils;
		Direction facingDir = model.GetFacingDirection();
		Vector2 moveVector = GetDirectionalVector(facingDir);
		moveVector *= -fallbackSpeed * fallbackPeriod;
		startPos = model.GetTransform().GetPos();
		finalPos = startPos + moveVector;
	}

	void PlayerFallbackStateHandler::OnUpdate()
	{
		float deltaTimeFromStart = Time::GetTime() - startTime;
		float normalizedFallbackTime = deltaTimeFromStart / fallbackPeriod;
		float playerImageHeight = 0.0f;
		if (normalizedFallbackTime < 1) {
			playerImageHeight = fallbackMaxHeight * std::sin(normalizedFallbackTime * (float)std::numbers::pi);
		} else {
			normalizedFallbackTime = 1;
		}

		// playerImageの高さ
		// TODO : Animatorで制御するようになる
		if (playerImageTransform == nullptr) {
			DEBUG_LOG_WARNING("playerImageTransform == nullptr。FallbackのUpdateがうまくいかない。");
		} else {
			playerImageTransform->SetPosY(playerImageHeight);
		}

		// playerの位置
		Vector2 pos = Vector2::Lerp(startPos, finalPos, normalizedFallbackTime);
		model.GetTransform().SetPos(pos);
	}

	void PlayerFallbackStateHandler::OnExit()
	{
		if (playerImageTransform != nullptr) {
			playerImageTransform->SetPosY(0.0f);
		}
		model.GetTransform().SetPos(finalPos);
	}

	bool PlayerFallbackStateHandler::CheckHasDoneState()
	{
		return Time::GetTime() - startTime >= fallbackPeriod;
	}
}

