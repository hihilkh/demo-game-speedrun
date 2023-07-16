#include "GE/GEHeader.h"
#include "PlayerCollisionHandler.h"
#include "GE/Collision/RectCollider.h"
#include "PlayerModel.h"
#include "PlayerConfig.h"
#include "GE/Utils/HandyFunc/CollisionRelated.h"
#include "Collision/CollisionInfo.h"


namespace Player
{
	PlayerCollisionHandler::PlayerCollisionHandler(GameObject& gameObject, PlayerModel& model, RectCollider& collider) :
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

	void PlayerCollisionHandler::HandleCollision(const Collider& other, CollidedType collidedType)
	{
		CollisionTypeWhileRunning collisionType = CheckCollisionTypeWhileRunning(other);
		switch (collisionType) {
			case CollisionTypeWhileRunning::Crash:
				model.Crash(other);
				break;
			case CollisionTypeWhileRunning::Hit:
				model.HitWall(other);
				break;
		}
	}

	// TODO : もっと良い方法を考える
	PlayerCollisionHandler::CollisionTypeWhileRunning PlayerCollisionHandler::CheckCollisionTypeWhileRunning(const Collider& other)
	{
		PlayerState state = model.GetPlayerState();
		if (state != PlayerState::Run && 
			state != PlayerState::StopRunning) {
			return CollisionTypeWhileRunning::Ignore;
		}

		if (other.GetCollisionLayer() != CollisionInfo::mapLayer) {
			return CollisionTypeWhileRunning::Ignore;
		}

		using namespace GE::Collision;

		// mapLayerのColliderは必ずRectColliderである
		auto otherRectCollider = dynamic_cast<const RectCollider*>(&other);
		if (otherRectCollider == nullptr) {
			DEBUG_LOG_WARNING("なぜかmapLayerのColliderはRectColliderではない");
			return CollisionTypeWhileRunning::Ignore;
		}

		CacheCollisionInfo();

		// 向かっていないCollisionをCrashしないように
		const Vector2& otherWorldPos = otherRectCollider->GetTransform().GetWorldPos();
		Rect otherRect = otherRectCollider->GetRect();
		otherRect.Move(otherWorldPos);

		Detection::CollidedType collidedType = CheckCollision(otherRect, facingDirMovementRect, 0.0f, 0.0f);
		switch (collidedType) {
			case Detection::CollidedType::Overlap:
				if (isOverCrashSpeed) {
					return CollisionTypeWhileRunning::Crash;
				} else {
					return CollisionTypeWhileRunning::Hit;
				}
			default:
				return CollisionTypeWhileRunning::Ignore;
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