#pragma once

#include <vector>
#include "GE/Utils/TypeDef.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	struct CollisionRecordImpl;

	class CollisionRecordHandler
	{
	public:
		void AddRecord(const CollisionRecordImpl& record);
		Vector2 CalculateAdjustmentAndClearRecords();

	private:
		// 一つのrecordは、posOffsetX または(つまり、or) posOffsetYが必要だと表す
		// また、recordのposOffsetの全ての成分も0ではないと想定する
		// recordsの中の全てのrecordも必要である(つまり、and)
		std::vector<CollisionRecordImpl> records;
	};
}