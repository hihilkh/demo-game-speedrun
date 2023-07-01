#pragma once

#include "GE/DataType/Transform2DData.h"
#include <memory>

namespace GE
{
	// TODO : 効率のために、WorldTransformをキャッシュするかどうかを考える
	class Transform2D : private Transform2DData
	{
	public:
		explicit Transform2D(
			GameObject& gameObject,
			const Vector2& pos = Vector2::zero,
			float rot = 0.0f);

		Transform2D(const Transform2D&) = delete;
		void operator=(const Transform2D&) = delete;

		const Vector2& GetPos() const { return pos; }
		float GetRot() const { return rot; }

		Vector2 GetWorldPos() const;
		float GetWorldRot() const;
		Transform2DData GetWorldTransformData() const;

		void SetPos(float x, float y);
		void SetPos(const Vector2& pos);
		void SetPosX(float x);
		void SetPosY(float y);
		void SetRot(float rot);

		void SetWorldPos(const Vector2& worldPos);
		void SetWorldRot(float worldRot);
	public:
		// Transform2DDataのメンバーをpublicになる
		//using Transform2DData::pos;
		//using Transform2DData::rot;

		// GameObjectが無効になる前に、必ず持っているTransform2Dを破棄するので、GameObjectの参照を持つ
		GameObject& gameObject;

	private:
		Vector2 GetWorldPos(const Transform2DData& parentWorldTransformData) const;
		float GetWorldRot(float parentWorldRot) const;

		bool CanChangePos() const;
	};
}