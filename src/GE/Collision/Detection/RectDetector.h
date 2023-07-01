#pragma once

#include "Detector.h"
#include <memory>

namespace GE::Collision::Detection
{
	class DetectorImpl;

	class RectDetector : public Detector
	{
	public:
		RectDetector(const RectCollider& collider);
		~RectDetector(); // DetectorImplが前方宣言できるために、デストラクタを宣言し、cppで定義する

		CollidedType CheckCollision(const RectCollider& other, RectDetector& otherDetector) override;

		void RecordCollision(CollisionRecord&& record) override;
		Vector2 GetCollisionAdjustmentPosOffset() override;

	private:
		std::unique_ptr<DetectorImpl> pImpl;
		const RectCollider& collider;
	};
}