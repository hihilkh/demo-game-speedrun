#pragma once

#include "Collider.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include "CollisionDetection/RectDetector.h"

namespace GE::Physics
{
	class RectCollider : public Collider, public CollisionDetection::RectDetector
	{
	public:
		RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect);

		const Rect& GetRect() const { return rect; }
		void SetRect(const Rect& rect) { this->rect = rect; }

#pragma region CollisionDetection

	private:
		CollisionDetection::CollidedType AcceptCollisionChecking(const CollisionDetection::Detector& detector) const override;
		void AcceptCollisionAdjustmentRecord(CollisionDetection::Detector& detector) override;

		virtual void AdjustCollidedPos() override;

		CollisionDetection::Detector& GetSelfDetector() override { return *this; }
		const CollisionDetection::Detector& GetSelfDetector() const override { return *this; }

		RectCollider& GetSelfCollider() override { return *this; }
		const RectCollider& GetSelfCollider() const override { return *this; }

#pragma endregion


	private:
		Rect rect;
	};
}