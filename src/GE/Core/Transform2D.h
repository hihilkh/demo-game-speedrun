#pragma once

#include "GE/DataType/Transform2DData.h"
#include <memory>

namespace GE
{
	// TODO : 効率のために、WorldTransformをキャッシュするかどうかを考える
	class Transform2D : public Internal::Transform2DData
	{
	public:
		// GameObjectが無効になる前に、必ず持っているTransform2Dを破棄するので、GameObjectの参照を持つ
		GameObject& gameObject;

		explicit Transform2D(
			GameObject& gameObject,
			const Vector2& pos = Vector2::zero,
			float rot = 0.0f);

		Transform2D(const Transform2D&) = delete;
		void operator=(const Transform2D&) = delete;

		void SetWorldPos(const Vector2& worldPos);
		void SetWorldRot(float worldRot);

		Vector2 GetWorldPos() const;
		float GetWorldRot() const;
		Internal::Transform2DData GetWorldTransformData() const;
	};
}