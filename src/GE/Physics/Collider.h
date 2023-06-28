#pragma once

#include "GE/Core/Component.h"
#include "GE/Core/Event.h"
#include "CollisionLayer.h"
#include "CollisionDetection/CollidedType.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"
#include <vector>

namespace GE::Physics
{
	namespace CollisionDetection
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
		Collider(GameObject& gameObject, bool isTrigger);
		virtual ~Collider() = default;

		bool GetIsTrigger() const { return isTrigger; }
		void SetIsTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

		CollisionLayer::Bitmask GetCollisionLayer() const { return layer; }
		void SetCollisionLayer(CollisionLayer::Bitmask layer) { this->layer = layer; }

	protected:
		void Start() override;
		void PreDestroy() override;

#pragma region CollisionDetection
	private:
		virtual CollisionDetection::CollidedType AcceptCollisionChecking(const CollisionDetection::Detector& detector) const = 0;
		virtual void AcceptCollisionAdjustmentRecord(CollisionDetection::Detector& detector) = 0;
		
		virtual CollisionDetection::Detector& GetSelfDetector() = 0;
		virtual const CollisionDetection::Detector& GetSelfDetector() const = 0;

		// CollisionSystemに呼び出される関数
		CollisionDetection::CollidedType CheckCollision(const Collider& other) const;
		void RecordCollisionAdjustment(Collider& other);

		virtual void AdjustCollidedPos() = 0;

#pragma endregion

	private:
		bool isTrigger;
		CollisionLayer::Bitmask layer;
	};
}
