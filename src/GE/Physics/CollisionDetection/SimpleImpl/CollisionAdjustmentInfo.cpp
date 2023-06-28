#include "CollisionAdjustmentInfo.h"
#include <algorithm>

namespace GE::Physics::CollisionDetection::SimpleImpl
{
	void CollisionAdjustmentInfo::AddInfo(float xOffset, float yOffset)
	{
		infos.emplace_back(xOffset, yOffset);
	}

	Vector2 CollisionAdjustmentInfo::CalculateAdjustmentAndClearInfos()
	{
		Vector2 result = Vector2::zero;
		float resultSqrMagnitude = 0.0f;
		if (infos.size() == 0) {
			return result;
		}

		std::vector<Vector2> optionsContainer1{ {0.0f, 0.0f} };
		std::vector<Vector2> optionsContainer2;

		std::vector<Vector2>* currentContainer = &optionsContainer1;
		std::vector<Vector2>* nextContainer = &optionsContainer2;

		for (const auto& info : infos) {
			for (const auto& option : (*currentContainer)) {
				// TODO : repeat code...

				// xによっての積集合
				if (info.x == 0) {
					nextContainer->emplace_back(option.x, option.y);
				} else if (option.x == 0) {
					nextContainer->emplace_back(info.x, option.y);
				} else if (option.x * info.x < 0) {
					// 矛盾になる。選択肢を追加しない。
				} else {
					float newX = option.x > 0 ? std::max(option.x, info.x) : std::min(option.x, info.x);
					nextContainer->emplace_back(newX, option.y);
				}

				// yによっての積集合
				if (info.y == 0) {
					nextContainer->emplace_back(option.x, option.y);
				} else if (option.y == 0) {
					nextContainer->emplace_back(option.x, info.y);
				} else if (option.y * info.y < 0) {
					// 矛盾になる。選択肢を追加しない。
				} else {
					float newY = option.y > 0 ? std::max(option.y, info.y) : std::min(option.y, info.y);
					nextContainer->emplace_back(option.x, newY);
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

		infos.clear();

		return result;
	}
}