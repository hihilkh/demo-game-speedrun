#include "GE/GEHeader.h"
#include "PlayerCollisionHandler.h"
#include "GE/Collision/RectCollider.h"
#include "PlayerModel.h"
#include "PlayerConfig.h"
#include "GE/Utils/HandyFunc/CollisionRelated.h"
#include "Collision/CollisionInfo.h"


namespace Player
{
	PlayerCollisionHandler::PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, GE::Collision::RectCollider& collider) :
		Component(gameObject),
		model(model),
		collider(collider),
		isCachedCollisionInfo(false),
		isOverCrashSpeed(false),
		facingDirMovementRect()
	{
	}

	void PlayerCollisionHandler::Start()
	{
		collider.onCollided.AddListener(&PlayerCollisionHandler::HandleCollision, *this);
	}
	
	void PlayerCollisionHandler::Update()
	{
		isCachedCollisionInfo = false;
	}

	void PlayerCollisionHandler::PreDestroy()
	{
		collider.onCollided.RemoveListener(&PlayerCollisionHandler::HandleCollision, *this);
	}

	void PlayerCollisionHandler::HandleCollision(const GE::Collision::Collider& other)
	{
		if (CheckIsCrash(other)) {
			model.Crash(other);
		}
	}

	// TODO : もっと良い方法を考える
	bool PlayerCollisionHandler::CheckIsCrash(const GE::Collision::Collider& other)
	{
		PlayerState state = model.GetPlayerState();
		if (state != PlayerState::Run && 
			state != PlayerState::StopRunning) {
			return false;
		}

		if (other.GetCollisionLayer() != CollisionInfo::mapLayer) {
			return false;
		}

		using namespace GE::Collision;

		// mapLayerのColliderは必ずRectColliderである
		auto otherRectCollider = dynamic_cast<const RectCollider*>(&other);
		if (otherRectCollider == nullptr) {
			DEBUG_LOG_WARNING("なぜかmapLayerのColliderはRectColliderではない");
			return false;
		}

		CacheCollisionInfo();
		if (!isOverCrashSpeed) {
			return false;
		}

		// 向かっていないCollisionをCrashしないように
		const Vector2& otherWorldPos = otherRectCollider->GetTransform().GetWorldPos();
		Rect otherRect = otherRectCollider->GetRect();
		otherRect.Move(otherWorldPos);

		Detection::CollidedType collidedType = CheckCollision(otherRect, facingDirMovementRect, 0.0f, 0.0f);
		switch (collidedType) {
			case Detection::CollidedType::Overlap:
				return true;
			default:
				return false;
		}
	}

	void PlayerCollisionHandler::CacheCollisionInfo()
	{
		if (isCachedCollisionInfo) {
			return;
		}

		using namespace TransformUtils;

		Direction facingDir = model.GetFacingDirection();
		Vector2 facingDirVector = GetDirectionalVector(facingDir);

		const Vector2& lastWorldPos = model.GetLastWorldPos();
		const Vector2& currentWorldPos = model.GetTransform().GetWorldPos();
		Vector2 moveVector = currentWorldPos - lastWorldPos;
		float facingDirMovement = Vector2::Dot(moveVector, facingDirVector);

		isOverCrashSpeed = facingDirMovement / Time::GetDeltaTime() >= crashSpeed;

		facingDirMovementRect = collider.GetRect();
		facingDirMovementRect.Move(lastWorldPos + facingDirVector * facingDirMovement);
	}
}