#pragma once

#include <memory>

#include "NonRotatedRectSimpleImpl/CollisionRecordImpl.h"

namespace GE::Collision::Detection
{
	class DetectorImpl;

	struct CollisionRecord : public NonRotatedRectSimpleImpl::CollisionRecordImpl
	{
		// 基底クラスのコンストラクタを使う
		using NonRotatedRectSimpleImpl::CollisionRecordImpl::CollisionRecordImpl;
	};

	std::unique_ptr<DetectorImpl> GenerateDetectorImpl();
}