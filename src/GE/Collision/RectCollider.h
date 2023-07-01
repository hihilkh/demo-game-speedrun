#pragma once

#include "Collider.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include "Detection/RectDetector.h"

namespace GE::Collision
{
	class RectCollider : public Collider
	{
	public:
		RectCollider(GameObject& gameObject, bool isTrigger, const Rect& rect);

		const Rect& GetRect() const { return rect; }
		void SetRect(const Rect& rect) { this->rect = rect; }

#pragma region Detection

	private:
		Detection::CollidedType AcceptCollisionChecking(Detection::Detector& fromDetector) override;

		Detection::Detector& GetSelfDetector() override { return detector; }
		const Detection::Detector& GetSelfDetector() const override { return detector; }

		virtual void AdjustCollidedPos() override;

#pragma endregion

	private:
		Rect rect;
		Detection::RectDetector detector;
	};
}