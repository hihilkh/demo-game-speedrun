#include "CollisionRelated.h"
#include "GE/Collision/Detection/DetectorFactory.h"
#include "GE/Collision/Detection/DetectorImpl.h"
#include <memory>

namespace GE::Collision
{
	namespace
	{
		std::unique_ptr<Detection::DetectorImpl> detector = Detection::GenerateDetectorImpl();
	}

	Detection::CollidedType CheckCollision(
		const Rect& lhsRect,
		const Rect& rhsRect,
		float lhsRot,
		float rhsRot)
	{
		return detector->CheckCollision(lhsRect, rhsRect, lhsRot, rhsRot);
	}
}