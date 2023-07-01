#pragma once

#include "GE/Core/Component.h"
#include "GE/Core/Event.h"
#include "CollisionLayer.h"
#include "Detection/CollidedType.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"
#include <vector>

namespace GE::Collision
{
	namespace Detection
	{
		class Detector;
	}
	class CollisionSystem;

	class Collider : public Component
	{
		friend CollisionSystem;

	public:
		// TODO : OnCollisionEnter / OnCollisionStay / OnCollisionExit のように分ける
		Event<const Collider&> onCollided;
		Event<const Collider&> onTriggered;

	public:
		Collider(GameObject& gameObject, bool isTrigger, bool isApplyCollisionAdjustment);
		virtual ~Collider() = default;

		bool GetIsTrigger() const { return isTrigger; }
		void SetIsTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

		bool GetIsApplyCollisionAdjustment() const { return isApplyCollisionAdjustment; }
		void SetIsApplyCollisionAdjustment(bool isApply) { isApplyCollisionAdjustment = isApply; }

		CollisionLayer::Bitmask GetCollisionLayer() const { return layer; }
		void SetCollisionLayer(CollisionLayer::Bitmask layer) { this->layer = layer; }

	protected:
		void Start() override;
		void PreDestroy() override;

#pragma region Detection
	private:
		virtual Detection::CollidedType AcceptCollisionChecking(Detection::Detector& fromDetector) = 0;

		virtual Detection::Detector& GetSelfDetector() = 0;
		virtual const Detection::Detector& GetSelfDetector() const = 0;

		// CollisionSystemに呼び出される関数
		Detection::CollidedType CheckCollision(Collider& other);
		virtual void AdjustCollidedPos() = 0;

#pragma endregion

	private:
		bool isTrigger;
		bool isApplyCollisionAdjustment;
		CollisionLayer::Bitmask layer;
	};
}
