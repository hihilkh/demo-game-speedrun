#include "DetectorFactory.h"
#include "NonRotatedRectSimpleImpl/DetectorImpl.h"

namespace GE::Collision::Detection
{
	class DetectorImpl;

	std::unique_ptr<DetectorImpl> GenerateDetectorImpl()
	{
		return std::make_unique<NonRotatedRectSimpleImpl::NonRotatedRectSimpleDetectorImpl>();
	}
}