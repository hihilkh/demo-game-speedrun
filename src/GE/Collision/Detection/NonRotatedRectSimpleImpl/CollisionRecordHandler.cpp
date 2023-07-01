#include "CollisionRecordHandler.h"
#include <algorithm>
#include "CollisionRecordImpl.h"
#include "GE/DataType/Vector2.h"

namespace GE::Collision::Detection::NonRotatedRectSimpleImpl
{
	void CollisionRecordHandler::AddRecord(const CollisionRecordImpl& record)
	{
		records.emplace_back(record.posOffset);
	}

	Vector2 CollisionRecordHandler::CalculateAdjustmentAndClearRecords()
	{
		Vector2 result = Vector2::zero;
		float resultSqrMagnitude = 0.0f;
		if (records.size() == 0) {
			return result;
		}

		std::vector<Vector2> optionsContainer1{ {0.0f, 0.0f} };
		std::vector<Vector2> optionsContainer2;

		std::vector<Vector2>* currentContainer = &optionsContainer1;
		std::vector<Vector2>* nextContainer = &optionsContainer2;

		for (const auto& record : records) {
			const Vector2& recordPosOffset = record.posOffset;
			for (const auto& option : (*currentContainer)) {
				// x,y成分によっての積集合
				for (std::size_t i = 0; i < Vector2::vectorSize; ++i) {
					Vector2 toAdd = option;

					// recordのposOffsetの全ての成分も0ではないと想定する
					//if (recordPosOffset[i] == 0) {
					//	nextContainer->emplace_back(std::move(toAdd));
					//} else 
					if (option[i] == 0) {
						toAdd[i] = recordPosOffset[i];
						nextContainer->emplace_back(std::move(toAdd));
					} else if (option[i] * recordPosOffset[i] < 0) {
						// 矛盾になる。選択肢を追加しない。
					} else {
						toAdd[i] = option[i] > 0 ? std::max(option[i], recordPosOffset[i]) : std::min(option[i], recordPosOffset[i]);
						nextContainer->emplace_back(std::move(toAdd));
					}
				}
			}

			std::swap(currentContainer, nextContainer);
			nextContainer->clear();
		}

		for (const auto& info : (*currentContainer)) {
			if (info == Vector2::zero) {
				continue;
			}

			float sqrMagnitude = info.SqrMagnitude();
			if (resultSqrMagnitude == 0 || sqrMagnitude < resultSqrMagnitude) {
				result = info;
				resultSqrMagnitude = sqrMagnitude;
			}
		}

		records.clear();

		return result;
	}
}